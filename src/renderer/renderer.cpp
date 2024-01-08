#include "renderer.h"
#include "../display/helper.h"
#include "../utils/debug.h"

using namespace renderer;

void Renderer::SetBackgroundMessage(const Message& message) {
  if (xSemaphoreTake(this->renderer_lock_, pdMS_TO_TICKS(1000)) != pdTRUE) {
    return;
  }
  DEBUG_PRINT_PREFIX("Setting background message\n");
  this->background_message_ = QueuedMessage{
      .message = message,
      .added_at = static_cast<uint64_t>(esp_timer_get_time() / 1000)};
  xSemaphoreGive(this->renderer_lock_);
}

void Renderer::SetMessage(const Message& message, uint32_t priority,
                          uint32_t duration) {
  if (xSemaphoreTake(this->renderer_lock_, pdMS_TO_TICKS(1000)) != pdTRUE) {
    return;
  }
  DEBUG_PRINT_PREFIX("Adding message\n");
  this->messages_[priority] = QueuedMessage{
      .message = message,
      .added_at = static_cast<uint64_t>(esp_timer_get_time() / 1000),
      .duration = duration};
  xSemaphoreGive(this->renderer_lock_);
};

bool Renderer::Start() {
  this->renderer_lock_ = xSemaphoreCreateMutex();
  if (this->renderer_lock_ == nullptr) {
    return false;
  }
  if (xTaskCreate(Renderer::RendererTask, "renderer-task", 0x1000, this, 3,
                  &this->renderer_task_) != pdPASS) {
    this->renderer_task_ = nullptr;
    return false;
  }
  return true;
}

void Renderer::Stop() {
  if (this->renderer_task_) {
    vTaskDelete(this->renderer_task_);
  }
  if (this->renderer_lock_) {
    vSemaphoreDelete(this->renderer_lock_);
  }
}

void Renderer::DrawMessage(const QueuedMessage& message, uint64_t time) {
  uint64_t time_from_start = time - message.added_at;

  if (message.message.brightness > this->display_->GetMaxBrightness()) {
    this->display_->SetBrightness(this->display_->GetMaxBrightness());
  } else {
    this->display_->SetBrightness(message.message.brightness);
  }

  switch (message.message.effect_type) {
    case EffectType::STATIC:
      this->DrawStaticText(message.message.data,
                           message.message.effect.static_effect.position,
                           false);
      break;
    case EffectType::RAW_BUFFER:
      this->DrawRawBuffer(message.message.data);
      break;
    case EffectType::FLASHING:
      this->DrawStaticText(
          message.message.data, message.message.effect.flashing_effect.position,
          (time_from_start / message.message.effect.flashing_effect.delay) % 2);
      break;
    case EffectType::SCROLL: {
      this->display_->Clear(false);
      int32_t initial_position =
          message.message.effect.scroll_effect.direction ==
                  Direction::LEFT_TO_RIGHT
              ? -display::DisplayHelper::GetStringWidth(*this->font_,
                                                        message.message.data)
              : this->display_->GetWidth();
      int32_t max_position = message.message.effect.scroll_effect.direction ==
                                     Direction::LEFT_TO_RIGHT
                                 ? this->display_->GetWidth()
                                 : -display::DisplayHelper::GetStringWidth(
                                       *this->font_, message.message.data);
      int32_t difference = std::abs(initial_position - max_position);
      int32_t current_time =
          time_from_start %
          (difference * 1000 / message.message.effect.scroll_effect.speed);
      int32_t shift =
          (current_time * message.message.effect.scroll_effect.speed) / 1000;
      display::DisplayHelper::DrawString(
          *this->display_, *this->font_, message.message.data,
          initial_position + (message.message.effect.scroll_effect.direction ==
                                      Direction::LEFT_TO_RIGHT
                                  ? shift
                                  : -shift),
          0, false);
      break;
    }
  }

  this->display_->Redraw();
}

void Renderer::DrawRawBuffer(const std::vector<uint8_t>& buffer) {
  std::vector<uint8_t> raw_buffer = buffer;
  raw_buffer.resize(this->display_->GetWidth() / 8 * 8);
  this->display_->SetRawBuffer(raw_buffer);
}

void Renderer::DrawStaticText(const std::vector<uint8_t>& data,
                              Position position, bool inversed) {
  this->display_->Clear(inversed);
  switch (position) {
    case Position::LEFT:
      display::DisplayHelper::DrawString(*this->display_, *this->font_, data, 0,
                                         0, inversed);
      return;
    case Position::RIGHT:
      display::DisplayHelper::DrawString(
          *this->display_, *this->font_, data,
          -display::DisplayHelper::GetStringWidth(*this->font_, data) +
              this->display_->GetWidth(),
          0, inversed);
      return;
    case Position::CENTER:
      display::DisplayHelper::DrawString(
          *this->display_, *this->font_, data,
          (this->display_->GetWidth() -
           display::DisplayHelper::GetStringWidth(*this->font_, data)) /
              2,
          0, inversed);
      return;
  }
}

void Renderer::RendererTask(void* raw_renderer) {
  const auto renderer = static_cast<Renderer*>(raw_renderer);

  while (true) {
    const auto time = static_cast<uint64_t>(esp_timer_get_time() / 1000);

    if (xSemaphoreTake(renderer->renderer_lock_, pdMS_TO_TICKS(1000)) != pdTRUE) {
      continue;
    }

    while (renderer->messages_.size()) {
      auto end_iterator = renderer->messages_.cend();
      end_iterator--;
      if (end_iterator->second.duration +
              end_iterator->second.added_at <
          time) {
        renderer->messages_.erase(end_iterator);
        continue;
      }
      break;
    }

    QueuedMessage current_message;

    if (renderer->messages_.size()) {
      auto end_iterator = renderer->messages_.cend();
      end_iterator--;
      current_message = end_iterator->second;
    } else {
      current_message = renderer->background_message_;
    }

    xSemaphoreGive(renderer->renderer_lock_);

    renderer->DrawMessage(current_message, time);
    vTaskDelay(5);
  }
}

Renderer::~Renderer() {
  this->Stop();
}
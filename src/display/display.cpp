#include "display.h"
#include "../utils/debug.h"

using namespace display;

static Display* current_display = nullptr;

IRAM_ATTR void Display::DisplayRefreshFunction() {
  if (!current_display) {
    return;
  }

  uint8_t current_row = current_display->current_row_;

  digitalWrite(current_display->latch_pin_, HIGH);
  for (int32_t zone = current_display->zones_ - 1; zone >= 0; zone--) {
    shiftOut(
        current_display->data_pin_, current_display->clk_pin_, MSBFIRST,
        current_display->brightness_step_ > current_display->brightness_
            ? 0
            : current_display
                  ->read_buffer_[current_row * current_display->zones_ + zone]);
  }
  shiftOut(current_display->data_pin_, current_display->clk_pin_, MSBFIRST,
           1 << current_row);
  digitalWrite(current_display->latch_pin_, LOW);

  current_row = (current_row + 1) % current_display->rows_;

  current_display->current_row_ = current_row;

  if (current_row == 0) {
    if (current_display->ready_to_swap_buffers_) {
      current_display->SwapBuffers();
      current_display->ready_to_swap_buffers_ = false;
      current_display->buffers_swapped_ = true;
    }
    current_display->brightness_step_ = (current_display->brightness_step_ + 1) %
                                        current_display->brightness_steps_;
  }
}

void Display::Start(uint32_t refresh_rate) {
  pinMode(this->clk_pin_, OUTPUT);
  pinMode(this->data_pin_, OUTPUT);
  pinMode(this->latch_pin_, OUTPUT);
  this->timer_ = timerBegin(500000);
  current_display = this;
  timerAttachInterrupt(this->timer_, DisplayRefreshFunction);
  timerAlarm(this->timer_, refresh_rate, true, 0);
}

Display::~Display() {
  current_display = nullptr;
  if (this->timer_) {
    timerDetachInterrupt(this->timer_);
    timerStop(this->timer_);
  }
}
 
void Display::Clear(bool fill) {
  std::fill(this->write_buffer_.begin(), this->write_buffer_.end(),
            fill ? 255 : 0);
}

void Display::SetPixel(int32_t x, int32_t y, bool enabled) {
  if (y >= this->rows_ || y < 0) {
    return;
  }
  if (x >= this->zones_ * 8 || x < 0) {
    return;
  }
  if (enabled) {
    this->write_buffer_[y * this->zones_ + x / 8] |= (1 << (x & 7));
  } else {
    this->write_buffer_[y * this->zones_ + x / 8] &= ~(1 << (x & 7));
  }
}

void Display::Redraw() {
  while (!this->buffers_swapped_) {
    delay(1);
  }

  this->buffers_swapped_ = false;
  this->ready_to_swap_buffers_ = true;
}

void Display::SwapBuffers() {
  std::swap(this->read_buffer_, this->write_buffer_);
}

void Display::SetBrightness(uint8_t brightness) {
  this->brightness_ = brightness;
}

void Display::SetBrightnessConfig(uint8_t brightness_steps) {
  this->brightness_steps_ = brightness_steps;
  this->brightness_step_ = 0;
}

uint8_t Display::GetMaxBrightness() const {
  return this->brightness_steps_;
}

uint32_t Display::GetWidth() const {
  return this->zones_ * 8;
}

std::vector<uint8_t>& Display::GetWriteBuffer() {
  return this->write_buffer_;
}

void Display::SetRawBuffer(const std::vector<uint8_t>& buffer) {
  std::copy(buffer.begin(), buffer.end(), this->write_buffer_.begin());
}
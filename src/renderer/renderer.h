#ifndef RENDERER_RENDERER_H_
#define RENDERER_RENDERER_H_

#include <Arduino.h>
#include <map>
#include <memory>

#include "../display/display.h"
#include "../display/font.h"
#include "message.h"

namespace renderer {

struct QueuedMessage {
  Message message;
  uint64_t added_at;
  uint32_t duration;
};

class Renderer {
 public:
  Renderer(std::shared_ptr<display::Display> display,
           std::shared_ptr<display::Font> font)
      : display_(display),
        font_(font),
        renderer_task_(nullptr),
        renderer_lock_(nullptr){};

  bool Start();
  void Stop();

  ~Renderer();

  void SetBackgroundMessage(const Message& message);
  void SetMessage(const Message& message, uint32_t priority, uint32_t duration);

 private:
  static void RendererTask(void* raw_renderer);
  void DrawMessage(const QueuedMessage& message, uint64_t time);
  void DrawStaticText(const std::vector<uint8_t>& data, Position position,
                      bool inversed);
  void DrawRawBuffer(const std::vector<uint8_t>& buffer);

  std::shared_ptr<display::Display> display_;
  std::shared_ptr<display::Font> font_;

  std::map<uint32_t, QueuedMessage> messages_;
  QueuedMessage background_message_;

  TaskHandle_t renderer_task_;
  SemaphoreHandle_t renderer_lock_;
};

}  // namespace renderer

#endif  //RENDERER_RENDERER_H_

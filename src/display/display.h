#ifndef DISPLAY_DISPLAY_H_
#define DISPLAY_DISPLAY_H_

#include <Arduino.h>
#include <cstdint>
#include <vector>

namespace display {

class Display {
 public:
  Display(uint32_t clk_pin, uint32_t data_pin, uint32_t latch_pin,
          uint32_t zones, uint32_t rows)
      : clk_pin_(clk_pin),
        data_pin_(data_pin),
        latch_pin_(latch_pin),
        zones_(zones),
        rows_(rows),
        current_row_(0),
        brightness_step_(0),
        brightness_steps_(4),
        brightness_(4),
        buffer1_(zones_ * rows_),
        buffer2_(zones_ * rows_),
        read_buffer_(buffer1_),
        write_buffer_(buffer2_),
        timer_(nullptr),
        buffers_swapped_(true),
        ready_to_swap_buffers_(false) {}

  void Start(uint32_t refresh_rate);
  void Clear(bool fill);
  void SetPixel(int32_t x, int32_t y, bool enabled);
  void Redraw();
  void SetBrightness(uint8_t brightness);
  void SetBrightnessConfig(uint8_t brightness_steps);
  void SetRawBuffer(const std::vector<uint8_t>& buffer);
  uint32_t GetWidth() const;
  uint8_t GetMaxBrightness() const;

  std::vector<uint8_t>& GetWriteBuffer();

  ~Display();

 private:
  void SwapBuffers();
  static void DisplayRefreshFunction();

  uint32_t clk_pin_;
  uint32_t data_pin_;
  uint32_t latch_pin_;

  uint32_t zones_;
  uint32_t rows_;

  uint8_t current_row_;
  uint8_t brightness_step_;
  uint8_t brightness_steps_;
  uint8_t brightness_;

  std::vector<uint8_t> buffer1_;
  std::vector<uint8_t> buffer2_;

  std::vector<uint8_t>& read_buffer_;
  std::vector<uint8_t>& write_buffer_;

  hw_timer_t* timer_;

  bool buffers_swapped_;
  bool ready_to_swap_buffers_;
};

}  // namespace display

#endif  //DISPLAY_DISPLAY_H_
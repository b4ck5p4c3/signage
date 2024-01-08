#ifndef DISPLAY_HELPER_H_
#define DISPLAY_HELPER_H_

#include "display.h"
#include "font.h"

#include <memory>

namespace display {

class DisplayHelper {
 public:
  static int32_t DrawString(Display& display, const Font& font,
                         const std::vector<uint8_t>& string, int32_t x, int32_t y,
                         bool inverse);
  static uint32_t GetStringWidth(const Font& font, const std::vector<uint8_t>& string);
};

}

#endif  //DISPLAY_HELPER_H_
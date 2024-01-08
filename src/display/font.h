#ifndef DISPLAY_FONT_H_
#define DISPLAY_FONT_H_

#include <cstdint>
#include <vector>

namespace display {

struct Font {
  std::vector<std::vector<uint8_t>> char_data;
  std::vector<uint8_t> char_widths;
};

}  // namespace display

#endif  //DISPLAY_FONT_H_
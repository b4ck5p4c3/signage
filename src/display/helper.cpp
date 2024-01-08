#include "helper.h"

using namespace display;

static int32_t DrawChar(Display& display, const Font& font, uint8_t c, int32_t x, int32_t y, bool inverse) {
  const std::vector<uint8_t>& char_data = font.char_data[c];
  for (int32_t i = 0; i < font.char_widths[c]; i++) {
    for (int32_t j = 0; j < 8; j++) {
      if (char_data[i] & (1 << j)) {
        display.SetPixel(x + i, y + j, !inverse);
      }
    }
  }
  return font.char_widths[c] + 2;
}

int32_t DisplayHelper::DrawString(Display& display, const Font& font,
                               const std::vector<uint8_t>& string, int32_t x, int32_t y,
                               bool inverse) {
  for (const auto c : string) {
    x += DrawChar(display, font, c, x, y, inverse);
  }
  return x;
}

uint32_t DisplayHelper::GetStringWidth(const Font& font, const std::vector<uint8_t>& string) {
  uint32_t result = string.size() * 2 - 2;
  for (const auto c : string) {
    result += font.char_widths[c];
  }
  return result;
}
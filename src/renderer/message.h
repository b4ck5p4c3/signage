#ifndef RENDERER_MESSAGE_H_
#define RENDERER_MESSAGE_H_

#include <vector>
#include <cstdint>

namespace renderer {

enum class EffectType {
  STATIC,
  SCROLL,
  FLASHING,
  RAW_BUFFER
};

enum class Position {
  LEFT = 0,
  CENTER = 1,
  RIGHT = 2
};

enum class Direction {
  LEFT_TO_RIGHT = 0,
  RIGHT_TO_LEFT = 1
};

struct StaticEffect {
  Position position;
};

struct ScrollEffect {
  Direction direction;
  uint32_t speed;
};

struct FlashingEffect {
  Position position;
  uint32_t delay;
};

union Effect {
  StaticEffect static_effect;
  ScrollEffect scroll_effect;
  FlashingEffect flashing_effect;
};

struct Message {
  std::vector<uint8_t> data;
  uint8_t brightness;
  EffectType effect_type;
  Effect effect;
};

}

#endif  //RENDERER_MESSAGE_H_
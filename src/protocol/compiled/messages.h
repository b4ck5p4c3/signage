/*
 *  This file is generated with Embedded Proto, PLEASE DO NOT EDIT!
 *  source: messages.proto
 */

// This file is generated. Please do not edit!
#ifndef MESSAGES_H
#define MESSAGES_H

#include <cstdint>
#include <MessageInterface.h>
#include <WireFormatter.h>
#include <Fields.h>
#include <MessageSizeCalculator.h>
#include <ReadBufferSection.h>
#include <RepeatedFieldFixedSize.h>
#include <FieldStringBytes.h>
#include <Errors.h>
#include <Defines.h>
#include <limits>

// Include external proto definitions

namespace protocol {

enum class Position : uint32_t
{
  LEFT = 0,
  CENTER = 1,
  RIGHT = 2
};

enum class Direction : uint32_t
{
  LEFT_TO_RIGHT = 0,
  RIGHT_TO_LEFT = 1
};

enum class EffectType : uint32_t
{
  STATIC = 0,
  SCROLL = 1,
  FLASH = 2,
  RAW_BUFFER = 3
};

class FlashEffect final: public ::EmbeddedProto::MessageInterface
{
  public:
    FlashEffect() = default;
    FlashEffect(const FlashEffect& rhs )
    {
      set_position(rhs.get_position());
      set_delay(rhs.get_delay());
    }

    FlashEffect(const FlashEffect&& rhs ) noexcept
    {
      set_position(rhs.get_position());
      set_delay(rhs.get_delay());
    }

    ~FlashEffect() override = default;

    enum class FieldNumber : uint32_t
    {
      NOT_SET = 0,
      POSITION = 1,
      DELAY = 2
    };

    FlashEffect& operator=(const FlashEffect& rhs)
    {
      set_position(rhs.get_position());
      set_delay(rhs.get_delay());
      return *this;
    }

    FlashEffect& operator=(const FlashEffect&& rhs) noexcept
    {
      set_position(rhs.get_position());
      set_delay(rhs.get_delay());
      return *this;
    }

    static constexpr char const* POSITION_NAME = "position";
    inline void clear_position() { position_.clear(); }
    inline void set_position(const Position& value) { position_ = value; }
    inline void set_position(const Position&& value) { position_ = value; }
    inline const Position& get_position() const { return position_.get(); }
    inline Position position() const { return position_.get(); }

    static constexpr char const* DELAY_NAME = "delay";
    inline void clear_delay() { delay_.clear(); }
    inline void set_delay(const uint32_t& value) { delay_ = value; }
    inline void set_delay(const uint32_t&& value) { delay_ = value; }
    inline uint32_t& mutable_delay() { return delay_.get(); }
    inline const uint32_t& get_delay() const { return delay_.get(); }
    inline uint32_t delay() const { return delay_.get(); }


    ::EmbeddedProto::Error serialize(::EmbeddedProto::WriteBufferInterface& buffer) const override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;

      if((static_cast<Position>(0) != position_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = position_.serialize_with_id(static_cast<uint32_t>(FieldNumber::POSITION), buffer, false);
      }

      if((0U != delay_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = delay_.serialize_with_id(static_cast<uint32_t>(FieldNumber::DELAY), buffer, false);
      }

      return return_value;
    };

    ::EmbeddedProto::Error deserialize(::EmbeddedProto::ReadBufferInterface& buffer) override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;
      ::EmbeddedProto::WireFormatter::WireType wire_type = ::EmbeddedProto::WireFormatter::WireType::VARINT;
      uint32_t id_number = 0;
      FieldNumber id_tag = FieldNumber::NOT_SET;

      ::EmbeddedProto::Error tag_value = ::EmbeddedProto::WireFormatter::DeserializeTag(buffer, wire_type, id_number);
      while((::EmbeddedProto::Error::NO_ERRORS == return_value) && (::EmbeddedProto::Error::NO_ERRORS == tag_value))
      {
        id_tag = static_cast<FieldNumber>(id_number);
        switch(id_tag)
        {
          case FieldNumber::POSITION:
            return_value = position_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::DELAY:
            return_value = delay_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::NOT_SET:
            return_value = ::EmbeddedProto::Error::INVALID_FIELD_ID;
            break;

          default:
            return_value = skip_unknown_field(buffer, wire_type);
            break;
        }

        if(::EmbeddedProto::Error::NO_ERRORS == return_value)
        {
          // Read the next tag.
          tag_value = ::EmbeddedProto::WireFormatter::DeserializeTag(buffer, wire_type, id_number);
        }
      }

      // When an error was detect while reading the tag but no other errors where found, set it in the return value.
      if((::EmbeddedProto::Error::NO_ERRORS == return_value)
         && (::EmbeddedProto::Error::NO_ERRORS != tag_value)
         && (::EmbeddedProto::Error::END_OF_BUFFER != tag_value)) // The end of the buffer is not an array in this case.
      {
        return_value = tag_value;
      }

      return return_value;
    };

    void clear() override
    {
      clear_position();
      clear_delay();

    }

    static char const* field_number_to_name(const FieldNumber fieldNumber)
    {
      char const* name = nullptr;
      switch(fieldNumber)
      {
        case FieldNumber::POSITION:
          name = POSITION_NAME;
          break;
        case FieldNumber::DELAY:
          name = DELAY_NAME;
          break;
        default:
          name = "Invalid FieldNumber";
          break;
      }
      return name;
    }

#ifdef MSG_TO_STRING

    ::EmbeddedProto::string_view to_string(::EmbeddedProto::string_view& str) const
    {
      return this->to_string(str, 0, nullptr, true);
    }

    ::EmbeddedProto::string_view to_string(::EmbeddedProto::string_view& str, const uint32_t indent_level, char const* name, const bool first_field) const override
    {
      ::EmbeddedProto::string_view left_chars = str;
      int32_t n_chars_used = 0;

      if(!first_field)
      {
        // Add a comma behind the previous field.
        n_chars_used = snprintf(left_chars.data, left_chars.size, ",\n");
        if(0 < n_chars_used)
        {
          // Update the character pointer and characters left in the array.
          left_chars.data += n_chars_used;
          left_chars.size -= n_chars_used;
        }
      }

      if(nullptr != name)
      {
        if( 0 == indent_level)
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "\"%s\": {\n", name);
        }
        else
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "%*s\"%s\": {\n", indent_level, " ", name);
        }
      }
      else
      {
        if( 0 == indent_level)
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "{\n");
        }
        else
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "%*s{\n", indent_level, " ");
        }
      }
      
      if(0 < n_chars_used)
      {
        left_chars.data += n_chars_used;
        left_chars.size -= n_chars_used;
      }

      left_chars = position_.to_string(left_chars, indent_level + 2, POSITION_NAME, true);
      left_chars = delay_.to_string(left_chars, indent_level + 2, DELAY_NAME, false);
  
      if( 0 == indent_level) 
      {
        n_chars_used = snprintf(left_chars.data, left_chars.size, "\n}");
      }
      else 
      {
        n_chars_used = snprintf(left_chars.data, left_chars.size, "\n%*s}", indent_level, " ");
      }

      if(0 < n_chars_used)
      {
        left_chars.data += n_chars_used;
        left_chars.size -= n_chars_used;
      }

      return left_chars;
    }

#endif // End of MSG_TO_STRING

  private:


      EmbeddedProto::enumeration<Position> position_ = static_cast<Position>(0);
      EmbeddedProto::uint32 delay_ = 0U;

};

class ScrollEffect final: public ::EmbeddedProto::MessageInterface
{
  public:
    ScrollEffect() = default;
    ScrollEffect(const ScrollEffect& rhs )
    {
      set_direction(rhs.get_direction());
      set_speed(rhs.get_speed());
    }

    ScrollEffect(const ScrollEffect&& rhs ) noexcept
    {
      set_direction(rhs.get_direction());
      set_speed(rhs.get_speed());
    }

    ~ScrollEffect() override = default;

    enum class FieldNumber : uint32_t
    {
      NOT_SET = 0,
      DIRECTION = 1,
      SPEED = 2
    };

    ScrollEffect& operator=(const ScrollEffect& rhs)
    {
      set_direction(rhs.get_direction());
      set_speed(rhs.get_speed());
      return *this;
    }

    ScrollEffect& operator=(const ScrollEffect&& rhs) noexcept
    {
      set_direction(rhs.get_direction());
      set_speed(rhs.get_speed());
      return *this;
    }

    static constexpr char const* DIRECTION_NAME = "direction";
    inline void clear_direction() { direction_.clear(); }
    inline void set_direction(const Direction& value) { direction_ = value; }
    inline void set_direction(const Direction&& value) { direction_ = value; }
    inline const Direction& get_direction() const { return direction_.get(); }
    inline Direction direction() const { return direction_.get(); }

    static constexpr char const* SPEED_NAME = "speed";
    inline void clear_speed() { speed_.clear(); }
    inline void set_speed(const uint32_t& value) { speed_ = value; }
    inline void set_speed(const uint32_t&& value) { speed_ = value; }
    inline uint32_t& mutable_speed() { return speed_.get(); }
    inline const uint32_t& get_speed() const { return speed_.get(); }
    inline uint32_t speed() const { return speed_.get(); }


    ::EmbeddedProto::Error serialize(::EmbeddedProto::WriteBufferInterface& buffer) const override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;

      if((static_cast<Direction>(0) != direction_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = direction_.serialize_with_id(static_cast<uint32_t>(FieldNumber::DIRECTION), buffer, false);
      }

      if((0U != speed_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = speed_.serialize_with_id(static_cast<uint32_t>(FieldNumber::SPEED), buffer, false);
      }

      return return_value;
    };

    ::EmbeddedProto::Error deserialize(::EmbeddedProto::ReadBufferInterface& buffer) override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;
      ::EmbeddedProto::WireFormatter::WireType wire_type = ::EmbeddedProto::WireFormatter::WireType::VARINT;
      uint32_t id_number = 0;
      FieldNumber id_tag = FieldNumber::NOT_SET;

      ::EmbeddedProto::Error tag_value = ::EmbeddedProto::WireFormatter::DeserializeTag(buffer, wire_type, id_number);
      while((::EmbeddedProto::Error::NO_ERRORS == return_value) && (::EmbeddedProto::Error::NO_ERRORS == tag_value))
      {
        id_tag = static_cast<FieldNumber>(id_number);
        switch(id_tag)
        {
          case FieldNumber::DIRECTION:
            return_value = direction_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::SPEED:
            return_value = speed_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::NOT_SET:
            return_value = ::EmbeddedProto::Error::INVALID_FIELD_ID;
            break;

          default:
            return_value = skip_unknown_field(buffer, wire_type);
            break;
        }

        if(::EmbeddedProto::Error::NO_ERRORS == return_value)
        {
          // Read the next tag.
          tag_value = ::EmbeddedProto::WireFormatter::DeserializeTag(buffer, wire_type, id_number);
        }
      }

      // When an error was detect while reading the tag but no other errors where found, set it in the return value.
      if((::EmbeddedProto::Error::NO_ERRORS == return_value)
         && (::EmbeddedProto::Error::NO_ERRORS != tag_value)
         && (::EmbeddedProto::Error::END_OF_BUFFER != tag_value)) // The end of the buffer is not an array in this case.
      {
        return_value = tag_value;
      }

      return return_value;
    };

    void clear() override
    {
      clear_direction();
      clear_speed();

    }

    static char const* field_number_to_name(const FieldNumber fieldNumber)
    {
      char const* name = nullptr;
      switch(fieldNumber)
      {
        case FieldNumber::DIRECTION:
          name = DIRECTION_NAME;
          break;
        case FieldNumber::SPEED:
          name = SPEED_NAME;
          break;
        default:
          name = "Invalid FieldNumber";
          break;
      }
      return name;
    }

#ifdef MSG_TO_STRING

    ::EmbeddedProto::string_view to_string(::EmbeddedProto::string_view& str) const
    {
      return this->to_string(str, 0, nullptr, true);
    }

    ::EmbeddedProto::string_view to_string(::EmbeddedProto::string_view& str, const uint32_t indent_level, char const* name, const bool first_field) const override
    {
      ::EmbeddedProto::string_view left_chars = str;
      int32_t n_chars_used = 0;

      if(!first_field)
      {
        // Add a comma behind the previous field.
        n_chars_used = snprintf(left_chars.data, left_chars.size, ",\n");
        if(0 < n_chars_used)
        {
          // Update the character pointer and characters left in the array.
          left_chars.data += n_chars_used;
          left_chars.size -= n_chars_used;
        }
      }

      if(nullptr != name)
      {
        if( 0 == indent_level)
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "\"%s\": {\n", name);
        }
        else
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "%*s\"%s\": {\n", indent_level, " ", name);
        }
      }
      else
      {
        if( 0 == indent_level)
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "{\n");
        }
        else
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "%*s{\n", indent_level, " ");
        }
      }
      
      if(0 < n_chars_used)
      {
        left_chars.data += n_chars_used;
        left_chars.size -= n_chars_used;
      }

      left_chars = direction_.to_string(left_chars, indent_level + 2, DIRECTION_NAME, true);
      left_chars = speed_.to_string(left_chars, indent_level + 2, SPEED_NAME, false);
  
      if( 0 == indent_level) 
      {
        n_chars_used = snprintf(left_chars.data, left_chars.size, "\n}");
      }
      else 
      {
        n_chars_used = snprintf(left_chars.data, left_chars.size, "\n%*s}", indent_level, " ");
      }

      if(0 < n_chars_used)
      {
        left_chars.data += n_chars_used;
        left_chars.size -= n_chars_used;
      }

      return left_chars;
    }

#endif // End of MSG_TO_STRING

  private:


      EmbeddedProto::enumeration<Direction> direction_ = static_cast<Direction>(0);
      EmbeddedProto::uint32 speed_ = 0U;

};

class StaticEffect final: public ::EmbeddedProto::MessageInterface
{
  public:
    StaticEffect() = default;
    StaticEffect(const StaticEffect& rhs )
    {
      set_position(rhs.get_position());
    }

    StaticEffect(const StaticEffect&& rhs ) noexcept
    {
      set_position(rhs.get_position());
    }

    ~StaticEffect() override = default;

    enum class FieldNumber : uint32_t
    {
      NOT_SET = 0,
      POSITION = 1
    };

    StaticEffect& operator=(const StaticEffect& rhs)
    {
      set_position(rhs.get_position());
      return *this;
    }

    StaticEffect& operator=(const StaticEffect&& rhs) noexcept
    {
      set_position(rhs.get_position());
      return *this;
    }

    static constexpr char const* POSITION_NAME = "position";
    inline void clear_position() { position_.clear(); }
    inline void set_position(const Position& value) { position_ = value; }
    inline void set_position(const Position&& value) { position_ = value; }
    inline const Position& get_position() const { return position_.get(); }
    inline Position position() const { return position_.get(); }


    ::EmbeddedProto::Error serialize(::EmbeddedProto::WriteBufferInterface& buffer) const override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;

      if((static_cast<Position>(0) != position_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = position_.serialize_with_id(static_cast<uint32_t>(FieldNumber::POSITION), buffer, false);
      }

      return return_value;
    };

    ::EmbeddedProto::Error deserialize(::EmbeddedProto::ReadBufferInterface& buffer) override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;
      ::EmbeddedProto::WireFormatter::WireType wire_type = ::EmbeddedProto::WireFormatter::WireType::VARINT;
      uint32_t id_number = 0;
      FieldNumber id_tag = FieldNumber::NOT_SET;

      ::EmbeddedProto::Error tag_value = ::EmbeddedProto::WireFormatter::DeserializeTag(buffer, wire_type, id_number);
      while((::EmbeddedProto::Error::NO_ERRORS == return_value) && (::EmbeddedProto::Error::NO_ERRORS == tag_value))
      {
        id_tag = static_cast<FieldNumber>(id_number);
        switch(id_tag)
        {
          case FieldNumber::POSITION:
            return_value = position_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::NOT_SET:
            return_value = ::EmbeddedProto::Error::INVALID_FIELD_ID;
            break;

          default:
            return_value = skip_unknown_field(buffer, wire_type);
            break;
        }

        if(::EmbeddedProto::Error::NO_ERRORS == return_value)
        {
          // Read the next tag.
          tag_value = ::EmbeddedProto::WireFormatter::DeserializeTag(buffer, wire_type, id_number);
        }
      }

      // When an error was detect while reading the tag but no other errors where found, set it in the return value.
      if((::EmbeddedProto::Error::NO_ERRORS == return_value)
         && (::EmbeddedProto::Error::NO_ERRORS != tag_value)
         && (::EmbeddedProto::Error::END_OF_BUFFER != tag_value)) // The end of the buffer is not an array in this case.
      {
        return_value = tag_value;
      }

      return return_value;
    };

    void clear() override
    {
      clear_position();

    }

    static char const* field_number_to_name(const FieldNumber fieldNumber)
    {
      char const* name = nullptr;
      switch(fieldNumber)
      {
        case FieldNumber::POSITION:
          name = POSITION_NAME;
          break;
        default:
          name = "Invalid FieldNumber";
          break;
      }
      return name;
    }

#ifdef MSG_TO_STRING

    ::EmbeddedProto::string_view to_string(::EmbeddedProto::string_view& str) const
    {
      return this->to_string(str, 0, nullptr, true);
    }

    ::EmbeddedProto::string_view to_string(::EmbeddedProto::string_view& str, const uint32_t indent_level, char const* name, const bool first_field) const override
    {
      ::EmbeddedProto::string_view left_chars = str;
      int32_t n_chars_used = 0;

      if(!first_field)
      {
        // Add a comma behind the previous field.
        n_chars_used = snprintf(left_chars.data, left_chars.size, ",\n");
        if(0 < n_chars_used)
        {
          // Update the character pointer and characters left in the array.
          left_chars.data += n_chars_used;
          left_chars.size -= n_chars_used;
        }
      }

      if(nullptr != name)
      {
        if( 0 == indent_level)
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "\"%s\": {\n", name);
        }
        else
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "%*s\"%s\": {\n", indent_level, " ", name);
        }
      }
      else
      {
        if( 0 == indent_level)
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "{\n");
        }
        else
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "%*s{\n", indent_level, " ");
        }
      }
      
      if(0 < n_chars_used)
      {
        left_chars.data += n_chars_used;
        left_chars.size -= n_chars_used;
      }

      left_chars = position_.to_string(left_chars, indent_level + 2, POSITION_NAME, true);
  
      if( 0 == indent_level) 
      {
        n_chars_used = snprintf(left_chars.data, left_chars.size, "\n}");
      }
      else 
      {
        n_chars_used = snprintf(left_chars.data, left_chars.size, "\n%*s}", indent_level, " ");
      }

      if(0 < n_chars_used)
      {
        left_chars.data += n_chars_used;
        left_chars.size -= n_chars_used;
      }

      return left_chars;
    }

#endif // End of MSG_TO_STRING

  private:


      EmbeddedProto::enumeration<Position> position_ = static_cast<Position>(0);

};

template<
    uint32_t Message_data_LENGTH
>
class Message final: public ::EmbeddedProto::MessageInterface
{
  public:
    Message() = default;
    Message(const Message& rhs )
    {
      set_data(rhs.get_data());
      set_brightness(rhs.get_brightness());
      set_effect_type(rhs.get_effect_type());
      if(rhs.get_which_effect() != which_effect_)
      {
        // First delete the old object in the oneof.
        clear_effect();
      }

      switch(rhs.get_which_effect())
      {
        case FieldNumber::STATIC_EFFECT:
          set_static_effect(rhs.get_static_effect());
          break;

        case FieldNumber::SCROLL_EFFECT:
          set_scroll_effect(rhs.get_scroll_effect());
          break;

        case FieldNumber::FLASH_EFFECT:
          set_flash_effect(rhs.get_flash_effect());
          break;

        default:
          break;
      }

    }

    Message(const Message&& rhs ) noexcept
    {
      set_data(rhs.get_data());
      set_brightness(rhs.get_brightness());
      set_effect_type(rhs.get_effect_type());
      if(rhs.get_which_effect() != which_effect_)
      {
        // First delete the old object in the oneof.
        clear_effect();
      }

      switch(rhs.get_which_effect())
      {
        case FieldNumber::STATIC_EFFECT:
          set_static_effect(rhs.get_static_effect());
          break;

        case FieldNumber::SCROLL_EFFECT:
          set_scroll_effect(rhs.get_scroll_effect());
          break;

        case FieldNumber::FLASH_EFFECT:
          set_flash_effect(rhs.get_flash_effect());
          break;

        default:
          break;
      }

    }

    ~Message() override = default;

    enum class FieldNumber : uint32_t
    {
      NOT_SET = 0,
      DATA = 1,
      BRIGHTNESS = 2,
      EFFECT_TYPE = 3,
      STATIC_EFFECT = 11,
      SCROLL_EFFECT = 12,
      FLASH_EFFECT = 13
    };

    Message& operator=(const Message& rhs)
    {
      set_data(rhs.get_data());
      set_brightness(rhs.get_brightness());
      set_effect_type(rhs.get_effect_type());
      if(rhs.get_which_effect() != which_effect_)
      {
        // First delete the old object in the oneof.
        clear_effect();
      }

      switch(rhs.get_which_effect())
      {
        case FieldNumber::STATIC_EFFECT:
          set_static_effect(rhs.get_static_effect());
          break;

        case FieldNumber::SCROLL_EFFECT:
          set_scroll_effect(rhs.get_scroll_effect());
          break;

        case FieldNumber::FLASH_EFFECT:
          set_flash_effect(rhs.get_flash_effect());
          break;

        default:
          break;
      }

      return *this;
    }

    Message& operator=(const Message&& rhs) noexcept
    {
      set_data(rhs.get_data());
      set_brightness(rhs.get_brightness());
      set_effect_type(rhs.get_effect_type());
      if(rhs.get_which_effect() != which_effect_)
      {
        // First delete the old object in the oneof.
        clear_effect();
      }

      switch(rhs.get_which_effect())
      {
        case FieldNumber::STATIC_EFFECT:
          set_static_effect(rhs.get_static_effect());
          break;

        case FieldNumber::SCROLL_EFFECT:
          set_scroll_effect(rhs.get_scroll_effect());
          break;

        case FieldNumber::FLASH_EFFECT:
          set_flash_effect(rhs.get_flash_effect());
          break;

        default:
          break;
      }

      return *this;
    }

    static constexpr char const* DATA_NAME = "data";
    inline void clear_data() { data_.clear(); }
    inline ::EmbeddedProto::FieldBytes<Message_data_LENGTH>& mutable_data() { return data_; }
    inline void set_data(const ::EmbeddedProto::FieldBytes<Message_data_LENGTH>& rhs) { data_.set(rhs); }
    inline const ::EmbeddedProto::FieldBytes<Message_data_LENGTH>& get_data() const { return data_; }
    inline const uint8_t* data() const { return data_.get_const(); }

    static constexpr char const* BRIGHTNESS_NAME = "brightness";
    inline void clear_brightness() { brightness_.clear(); }
    inline void set_brightness(const uint32_t& value) { brightness_ = value; }
    inline void set_brightness(const uint32_t&& value) { brightness_ = value; }
    inline uint32_t& mutable_brightness() { return brightness_.get(); }
    inline const uint32_t& get_brightness() const { return brightness_.get(); }
    inline uint32_t brightness() const { return brightness_.get(); }

    static constexpr char const* EFFECT_TYPE_NAME = "effect_type";
    inline void clear_effect_type() { effect_type_.clear(); }
    inline void set_effect_type(const EffectType& value) { effect_type_ = value; }
    inline void set_effect_type(const EffectType&& value) { effect_type_ = value; }
    inline const EffectType& get_effect_type() const { return effect_type_.get(); }
    inline EffectType effect_type() const { return effect_type_.get(); }

    FieldNumber get_which_effect() const { return which_effect_; }

    static constexpr char const* STATIC_EFFECT_NAME = "static_effect";
    inline bool has_static_effect() const
    {
      return FieldNumber::STATIC_EFFECT == which_effect_;
    }
    inline void clear_static_effect()
    {
      if(FieldNumber::STATIC_EFFECT == which_effect_)
      {
        which_effect_ = FieldNumber::NOT_SET;
        effect_.static_effect_.~StaticEffect();
      }
    }
    inline void set_static_effect(const StaticEffect& value)
    {
      if(FieldNumber::STATIC_EFFECT != which_effect_)
      {
        init_effect(FieldNumber::STATIC_EFFECT);
      }
      effect_.static_effect_ = value;
    }
    inline void set_static_effect(const StaticEffect&& value)
    {
      if(FieldNumber::STATIC_EFFECT != which_effect_)
      {
        init_effect(FieldNumber::STATIC_EFFECT);
      }
      effect_.static_effect_ = value;
    }
    inline StaticEffect& mutable_static_effect()
    {
      if(FieldNumber::STATIC_EFFECT != which_effect_)
      {
        init_effect(FieldNumber::STATIC_EFFECT);
      }
      return effect_.static_effect_;
    }
    inline const StaticEffect& get_static_effect() const { return effect_.static_effect_; }
    inline const StaticEffect& static_effect() const { return effect_.static_effect_; }

    static constexpr char const* SCROLL_EFFECT_NAME = "scroll_effect";
    inline bool has_scroll_effect() const
    {
      return FieldNumber::SCROLL_EFFECT == which_effect_;
    }
    inline void clear_scroll_effect()
    {
      if(FieldNumber::SCROLL_EFFECT == which_effect_)
      {
        which_effect_ = FieldNumber::NOT_SET;
        effect_.scroll_effect_.~ScrollEffect();
      }
    }
    inline void set_scroll_effect(const ScrollEffect& value)
    {
      if(FieldNumber::SCROLL_EFFECT != which_effect_)
      {
        init_effect(FieldNumber::SCROLL_EFFECT);
      }
      effect_.scroll_effect_ = value;
    }
    inline void set_scroll_effect(const ScrollEffect&& value)
    {
      if(FieldNumber::SCROLL_EFFECT != which_effect_)
      {
        init_effect(FieldNumber::SCROLL_EFFECT);
      }
      effect_.scroll_effect_ = value;
    }
    inline ScrollEffect& mutable_scroll_effect()
    {
      if(FieldNumber::SCROLL_EFFECT != which_effect_)
      {
        init_effect(FieldNumber::SCROLL_EFFECT);
      }
      return effect_.scroll_effect_;
    }
    inline const ScrollEffect& get_scroll_effect() const { return effect_.scroll_effect_; }
    inline const ScrollEffect& scroll_effect() const { return effect_.scroll_effect_; }

    static constexpr char const* FLASH_EFFECT_NAME = "flash_effect";
    inline bool has_flash_effect() const
    {
      return FieldNumber::FLASH_EFFECT == which_effect_;
    }
    inline void clear_flash_effect()
    {
      if(FieldNumber::FLASH_EFFECT == which_effect_)
      {
        which_effect_ = FieldNumber::NOT_SET;
        effect_.flash_effect_.~FlashEffect();
      }
    }
    inline void set_flash_effect(const FlashEffect& value)
    {
      if(FieldNumber::FLASH_EFFECT != which_effect_)
      {
        init_effect(FieldNumber::FLASH_EFFECT);
      }
      effect_.flash_effect_ = value;
    }
    inline void set_flash_effect(const FlashEffect&& value)
    {
      if(FieldNumber::FLASH_EFFECT != which_effect_)
      {
        init_effect(FieldNumber::FLASH_EFFECT);
      }
      effect_.flash_effect_ = value;
    }
    inline FlashEffect& mutable_flash_effect()
    {
      if(FieldNumber::FLASH_EFFECT != which_effect_)
      {
        init_effect(FieldNumber::FLASH_EFFECT);
      }
      return effect_.flash_effect_;
    }
    inline const FlashEffect& get_flash_effect() const { return effect_.flash_effect_; }
    inline const FlashEffect& flash_effect() const { return effect_.flash_effect_; }


    ::EmbeddedProto::Error serialize(::EmbeddedProto::WriteBufferInterface& buffer) const override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;

      if(::EmbeddedProto::Error::NO_ERRORS == return_value)
      {
        return_value = data_.serialize_with_id(static_cast<uint32_t>(FieldNumber::DATA), buffer, false);
      }

      if((0U != brightness_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = brightness_.serialize_with_id(static_cast<uint32_t>(FieldNumber::BRIGHTNESS), buffer, false);
      }

      if((static_cast<EffectType>(0) != effect_type_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = effect_type_.serialize_with_id(static_cast<uint32_t>(FieldNumber::EFFECT_TYPE), buffer, false);
      }

      switch(which_effect_)
      {
        case FieldNumber::STATIC_EFFECT:
          if(has_static_effect() && (::EmbeddedProto::Error::NO_ERRORS == return_value))
          {
            return_value = effect_.static_effect_.serialize_with_id(static_cast<uint32_t>(FieldNumber::STATIC_EFFECT), buffer, true);
          }
          break;

        case FieldNumber::SCROLL_EFFECT:
          if(has_scroll_effect() && (::EmbeddedProto::Error::NO_ERRORS == return_value))
          {
            return_value = effect_.scroll_effect_.serialize_with_id(static_cast<uint32_t>(FieldNumber::SCROLL_EFFECT), buffer, true);
          }
          break;

        case FieldNumber::FLASH_EFFECT:
          if(has_flash_effect() && (::EmbeddedProto::Error::NO_ERRORS == return_value))
          {
            return_value = effect_.flash_effect_.serialize_with_id(static_cast<uint32_t>(FieldNumber::FLASH_EFFECT), buffer, true);
          }
          break;

        default:
          break;
      }

      return return_value;
    };

    ::EmbeddedProto::Error deserialize(::EmbeddedProto::ReadBufferInterface& buffer) override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;
      ::EmbeddedProto::WireFormatter::WireType wire_type = ::EmbeddedProto::WireFormatter::WireType::VARINT;
      uint32_t id_number = 0;
      FieldNumber id_tag = FieldNumber::NOT_SET;

      ::EmbeddedProto::Error tag_value = ::EmbeddedProto::WireFormatter::DeserializeTag(buffer, wire_type, id_number);
      while((::EmbeddedProto::Error::NO_ERRORS == return_value) && (::EmbeddedProto::Error::NO_ERRORS == tag_value))
      {
        id_tag = static_cast<FieldNumber>(id_number);
        switch(id_tag)
        {
          case FieldNumber::DATA:
            return_value = data_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::BRIGHTNESS:
            return_value = brightness_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::EFFECT_TYPE:
            return_value = effect_type_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::STATIC_EFFECT:
          case FieldNumber::SCROLL_EFFECT:
          case FieldNumber::FLASH_EFFECT:
            return_value = deserialize_effect(id_tag, buffer, wire_type);
            break;

          case FieldNumber::NOT_SET:
            return_value = ::EmbeddedProto::Error::INVALID_FIELD_ID;
            break;

          default:
            return_value = skip_unknown_field(buffer, wire_type);
            break;
        }

        if(::EmbeddedProto::Error::NO_ERRORS == return_value)
        {
          // Read the next tag.
          tag_value = ::EmbeddedProto::WireFormatter::DeserializeTag(buffer, wire_type, id_number);
        }
      }

      // When an error was detect while reading the tag but no other errors where found, set it in the return value.
      if((::EmbeddedProto::Error::NO_ERRORS == return_value)
         && (::EmbeddedProto::Error::NO_ERRORS != tag_value)
         && (::EmbeddedProto::Error::END_OF_BUFFER != tag_value)) // The end of the buffer is not an array in this case.
      {
        return_value = tag_value;
      }

      return return_value;
    };

    void clear() override
    {
      clear_data();
      clear_brightness();
      clear_effect_type();
      clear_effect();

    }

    static char const* field_number_to_name(const FieldNumber fieldNumber)
    {
      char const* name = nullptr;
      switch(fieldNumber)
      {
        case FieldNumber::DATA:
          name = DATA_NAME;
          break;
        case FieldNumber::BRIGHTNESS:
          name = BRIGHTNESS_NAME;
          break;
        case FieldNumber::EFFECT_TYPE:
          name = EFFECT_TYPE_NAME;
          break;
        case FieldNumber::STATIC_EFFECT:
          name = STATIC_EFFECT_NAME;
          break;
        case FieldNumber::SCROLL_EFFECT:
          name = SCROLL_EFFECT_NAME;
          break;
        case FieldNumber::FLASH_EFFECT:
          name = FLASH_EFFECT_NAME;
          break;
        default:
          name = "Invalid FieldNumber";
          break;
      }
      return name;
    }

#ifdef MSG_TO_STRING

    ::EmbeddedProto::string_view to_string(::EmbeddedProto::string_view& str) const
    {
      return this->to_string(str, 0, nullptr, true);
    }

    ::EmbeddedProto::string_view to_string(::EmbeddedProto::string_view& str, const uint32_t indent_level, char const* name, const bool first_field) const override
    {
      ::EmbeddedProto::string_view left_chars = str;
      int32_t n_chars_used = 0;

      if(!first_field)
      {
        // Add a comma behind the previous field.
        n_chars_used = snprintf(left_chars.data, left_chars.size, ",\n");
        if(0 < n_chars_used)
        {
          // Update the character pointer and characters left in the array.
          left_chars.data += n_chars_used;
          left_chars.size -= n_chars_used;
        }
      }

      if(nullptr != name)
      {
        if( 0 == indent_level)
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "\"%s\": {\n", name);
        }
        else
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "%*s\"%s\": {\n", indent_level, " ", name);
        }
      }
      else
      {
        if( 0 == indent_level)
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "{\n");
        }
        else
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "%*s{\n", indent_level, " ");
        }
      }
      
      if(0 < n_chars_used)
      {
        left_chars.data += n_chars_used;
        left_chars.size -= n_chars_used;
      }

      left_chars = data_.to_string(left_chars, indent_level + 2, DATA_NAME, true);
      left_chars = brightness_.to_string(left_chars, indent_level + 2, BRIGHTNESS_NAME, false);
      left_chars = effect_type_.to_string(left_chars, indent_level + 2, EFFECT_TYPE_NAME, false);
      left_chars = to_string_effect(left_chars, indent_level + 2, false);
  
      if( 0 == indent_level) 
      {
        n_chars_used = snprintf(left_chars.data, left_chars.size, "\n}");
      }
      else 
      {
        n_chars_used = snprintf(left_chars.data, left_chars.size, "\n%*s}", indent_level, " ");
      }

      if(0 < n_chars_used)
      {
        left_chars.data += n_chars_used;
        left_chars.size -= n_chars_used;
      }

      return left_chars;
    }

#endif // End of MSG_TO_STRING

  private:


      ::EmbeddedProto::FieldBytes<Message_data_LENGTH> data_;
      EmbeddedProto::uint32 brightness_ = 0U;
      EmbeddedProto::enumeration<EffectType> effect_type_ = static_cast<EffectType>(0);

      FieldNumber which_effect_ = FieldNumber::NOT_SET;
      union effect
      {
        effect() {}
        ~effect() {}
        StaticEffect static_effect_;
        ScrollEffect scroll_effect_;
        FlashEffect flash_effect_;
      };
      effect effect_;

      void init_effect(const FieldNumber field_id)
      {
        if(FieldNumber::NOT_SET != which_effect_)
        {
          // First delete the old object in the oneof.
          clear_effect();
        }

        // C++11 unions only support nontrivial members when you explicitly call the placement new statement.
        switch(field_id)
        {
          case FieldNumber::STATIC_EFFECT:
            new(&effect_.static_effect_) StaticEffect;
            break;

          case FieldNumber::SCROLL_EFFECT:
            new(&effect_.scroll_effect_) ScrollEffect;
            break;

          case FieldNumber::FLASH_EFFECT:
            new(&effect_.flash_effect_) FlashEffect;
            break;

          default:
            break;
         }

         which_effect_ = field_id;
      }

      void clear_effect()
      {
        switch(which_effect_)
        {
          case FieldNumber::STATIC_EFFECT:
            ::EmbeddedProto::destroy_at(&effect_.static_effect_);
            break;
          case FieldNumber::SCROLL_EFFECT:
            ::EmbeddedProto::destroy_at(&effect_.scroll_effect_);
            break;
          case FieldNumber::FLASH_EFFECT:
            ::EmbeddedProto::destroy_at(&effect_.flash_effect_);
            break;
          default:
            break;
        }
        which_effect_ = FieldNumber::NOT_SET;
      }

      ::EmbeddedProto::Error deserialize_effect(const FieldNumber field_id, 
                                    ::EmbeddedProto::ReadBufferInterface& buffer,
                                    const ::EmbeddedProto::WireFormatter::WireType wire_type)
      {
        ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;
        
        if(field_id != which_effect_)
        {
          init_effect(field_id);
        }

        switch(which_effect_)
        {
          case FieldNumber::STATIC_EFFECT:
            return_value = effect_.static_effect_.deserialize_check_type(buffer, wire_type);
            break;
          case FieldNumber::SCROLL_EFFECT:
            return_value = effect_.scroll_effect_.deserialize_check_type(buffer, wire_type);
            break;
          case FieldNumber::FLASH_EFFECT:
            return_value = effect_.flash_effect_.deserialize_check_type(buffer, wire_type);
            break;
          default:
            break;
        }

        if(::EmbeddedProto::Error::NO_ERRORS != return_value)
        {
          clear_effect();
        }
        return return_value;
      }

#ifdef MSG_TO_STRING 
      ::EmbeddedProto::string_view to_string_effect(::EmbeddedProto::string_view& str, const uint32_t indent_level, const bool first_field) const
      {
        ::EmbeddedProto::string_view left_chars = str;

        switch(which_effect_)
        {
          case FieldNumber::STATIC_EFFECT:
            left_chars = effect_.static_effect_.to_string(left_chars, indent_level, STATIC_EFFECT_NAME, first_field);
            break;
          case FieldNumber::SCROLL_EFFECT:
            left_chars = effect_.scroll_effect_.to_string(left_chars, indent_level, SCROLL_EFFECT_NAME, first_field);
            break;
          case FieldNumber::FLASH_EFFECT:
            left_chars = effect_.flash_effect_.to_string(left_chars, indent_level, FLASH_EFFECT_NAME, first_field);
            break;
          default:
            break;
        }

        return left_chars;
      }

#endif // End of MSG_TO_STRING
};

template<
    uint32_t SetBackgroundMessagePacket_message_Message_data_LENGTH
>
class SetBackgroundMessagePacket final: public ::EmbeddedProto::MessageInterface
{
  public:
    SetBackgroundMessagePacket() = default;
    SetBackgroundMessagePacket(const SetBackgroundMessagePacket& rhs )
    {
      set_message(rhs.get_message());
    }

    SetBackgroundMessagePacket(const SetBackgroundMessagePacket&& rhs ) noexcept
    {
      set_message(rhs.get_message());
    }

    ~SetBackgroundMessagePacket() override = default;

    enum class FieldNumber : uint32_t
    {
      NOT_SET = 0,
      MESSAGE = 1
    };

    SetBackgroundMessagePacket& operator=(const SetBackgroundMessagePacket& rhs)
    {
      set_message(rhs.get_message());
      return *this;
    }

    SetBackgroundMessagePacket& operator=(const SetBackgroundMessagePacket&& rhs) noexcept
    {
      set_message(rhs.get_message());
      return *this;
    }

    static constexpr char const* MESSAGE_NAME = "message";
    inline void clear_message() { message_.clear(); }
    inline void set_message(const Message<SetBackgroundMessagePacket_message_Message_data_LENGTH>& value) { message_ = value; }
    inline void set_message(const Message<SetBackgroundMessagePacket_message_Message_data_LENGTH>&& value) { message_ = value; }
    inline Message<SetBackgroundMessagePacket_message_Message_data_LENGTH>& mutable_message() { return message_; }
    inline const Message<SetBackgroundMessagePacket_message_Message_data_LENGTH>& get_message() const { return message_; }
    inline const Message<SetBackgroundMessagePacket_message_Message_data_LENGTH>& message() const { return message_; }


    ::EmbeddedProto::Error serialize(::EmbeddedProto::WriteBufferInterface& buffer) const override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;

      if(::EmbeddedProto::Error::NO_ERRORS == return_value)
      {
        return_value = message_.serialize_with_id(static_cast<uint32_t>(FieldNumber::MESSAGE), buffer, false);
      }

      return return_value;
    };

    ::EmbeddedProto::Error deserialize(::EmbeddedProto::ReadBufferInterface& buffer) override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;
      ::EmbeddedProto::WireFormatter::WireType wire_type = ::EmbeddedProto::WireFormatter::WireType::VARINT;
      uint32_t id_number = 0;
      FieldNumber id_tag = FieldNumber::NOT_SET;

      ::EmbeddedProto::Error tag_value = ::EmbeddedProto::WireFormatter::DeserializeTag(buffer, wire_type, id_number);
      while((::EmbeddedProto::Error::NO_ERRORS == return_value) && (::EmbeddedProto::Error::NO_ERRORS == tag_value))
      {
        id_tag = static_cast<FieldNumber>(id_number);
        switch(id_tag)
        {
          case FieldNumber::MESSAGE:
            return_value = message_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::NOT_SET:
            return_value = ::EmbeddedProto::Error::INVALID_FIELD_ID;
            break;

          default:
            return_value = skip_unknown_field(buffer, wire_type);
            break;
        }

        if(::EmbeddedProto::Error::NO_ERRORS == return_value)
        {
          // Read the next tag.
          tag_value = ::EmbeddedProto::WireFormatter::DeserializeTag(buffer, wire_type, id_number);
        }
      }

      // When an error was detect while reading the tag but no other errors where found, set it in the return value.
      if((::EmbeddedProto::Error::NO_ERRORS == return_value)
         && (::EmbeddedProto::Error::NO_ERRORS != tag_value)
         && (::EmbeddedProto::Error::END_OF_BUFFER != tag_value)) // The end of the buffer is not an array in this case.
      {
        return_value = tag_value;
      }

      return return_value;
    };

    void clear() override
    {
      clear_message();

    }

    static char const* field_number_to_name(const FieldNumber fieldNumber)
    {
      char const* name = nullptr;
      switch(fieldNumber)
      {
        case FieldNumber::MESSAGE:
          name = MESSAGE_NAME;
          break;
        default:
          name = "Invalid FieldNumber";
          break;
      }
      return name;
    }

#ifdef MSG_TO_STRING

    ::EmbeddedProto::string_view to_string(::EmbeddedProto::string_view& str) const
    {
      return this->to_string(str, 0, nullptr, true);
    }

    ::EmbeddedProto::string_view to_string(::EmbeddedProto::string_view& str, const uint32_t indent_level, char const* name, const bool first_field) const override
    {
      ::EmbeddedProto::string_view left_chars = str;
      int32_t n_chars_used = 0;

      if(!first_field)
      {
        // Add a comma behind the previous field.
        n_chars_used = snprintf(left_chars.data, left_chars.size, ",\n");
        if(0 < n_chars_used)
        {
          // Update the character pointer and characters left in the array.
          left_chars.data += n_chars_used;
          left_chars.size -= n_chars_used;
        }
      }

      if(nullptr != name)
      {
        if( 0 == indent_level)
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "\"%s\": {\n", name);
        }
        else
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "%*s\"%s\": {\n", indent_level, " ", name);
        }
      }
      else
      {
        if( 0 == indent_level)
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "{\n");
        }
        else
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "%*s{\n", indent_level, " ");
        }
      }
      
      if(0 < n_chars_used)
      {
        left_chars.data += n_chars_used;
        left_chars.size -= n_chars_used;
      }

      left_chars = message_.to_string(left_chars, indent_level + 2, MESSAGE_NAME, true);
  
      if( 0 == indent_level) 
      {
        n_chars_used = snprintf(left_chars.data, left_chars.size, "\n}");
      }
      else 
      {
        n_chars_used = snprintf(left_chars.data, left_chars.size, "\n%*s}", indent_level, " ");
      }

      if(0 < n_chars_used)
      {
        left_chars.data += n_chars_used;
        left_chars.size -= n_chars_used;
      }

      return left_chars;
    }

#endif // End of MSG_TO_STRING

  private:


      Message<SetBackgroundMessagePacket_message_Message_data_LENGTH> message_;

};

template<
    uint32_t SetMessagePacket_message_Message_data_LENGTH
>
class SetMessagePacket final: public ::EmbeddedProto::MessageInterface
{
  public:
    SetMessagePacket() = default;
    SetMessagePacket(const SetMessagePacket& rhs )
    {
      set_message(rhs.get_message());
      set_priority(rhs.get_priority());
      set_duration(rhs.get_duration());
    }

    SetMessagePacket(const SetMessagePacket&& rhs ) noexcept
    {
      set_message(rhs.get_message());
      set_priority(rhs.get_priority());
      set_duration(rhs.get_duration());
    }

    ~SetMessagePacket() override = default;

    enum class FieldNumber : uint32_t
    {
      NOT_SET = 0,
      MESSAGE = 1,
      PRIORITY = 2,
      DURATION = 3
    };

    SetMessagePacket& operator=(const SetMessagePacket& rhs)
    {
      set_message(rhs.get_message());
      set_priority(rhs.get_priority());
      set_duration(rhs.get_duration());
      return *this;
    }

    SetMessagePacket& operator=(const SetMessagePacket&& rhs) noexcept
    {
      set_message(rhs.get_message());
      set_priority(rhs.get_priority());
      set_duration(rhs.get_duration());
      return *this;
    }

    static constexpr char const* MESSAGE_NAME = "message";
    inline void clear_message() { message_.clear(); }
    inline void set_message(const Message<SetMessagePacket_message_Message_data_LENGTH>& value) { message_ = value; }
    inline void set_message(const Message<SetMessagePacket_message_Message_data_LENGTH>&& value) { message_ = value; }
    inline Message<SetMessagePacket_message_Message_data_LENGTH>& mutable_message() { return message_; }
    inline const Message<SetMessagePacket_message_Message_data_LENGTH>& get_message() const { return message_; }
    inline const Message<SetMessagePacket_message_Message_data_LENGTH>& message() const { return message_; }

    static constexpr char const* PRIORITY_NAME = "priority";
    inline void clear_priority() { priority_.clear(); }
    inline void set_priority(const uint32_t& value) { priority_ = value; }
    inline void set_priority(const uint32_t&& value) { priority_ = value; }
    inline uint32_t& mutable_priority() { return priority_.get(); }
    inline const uint32_t& get_priority() const { return priority_.get(); }
    inline uint32_t priority() const { return priority_.get(); }

    static constexpr char const* DURATION_NAME = "duration";
    inline void clear_duration() { duration_.clear(); }
    inline void set_duration(const uint32_t& value) { duration_ = value; }
    inline void set_duration(const uint32_t&& value) { duration_ = value; }
    inline uint32_t& mutable_duration() { return duration_.get(); }
    inline const uint32_t& get_duration() const { return duration_.get(); }
    inline uint32_t duration() const { return duration_.get(); }


    ::EmbeddedProto::Error serialize(::EmbeddedProto::WriteBufferInterface& buffer) const override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;

      if(::EmbeddedProto::Error::NO_ERRORS == return_value)
      {
        return_value = message_.serialize_with_id(static_cast<uint32_t>(FieldNumber::MESSAGE), buffer, false);
      }

      if((0U != priority_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = priority_.serialize_with_id(static_cast<uint32_t>(FieldNumber::PRIORITY), buffer, false);
      }

      if((0U != duration_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = duration_.serialize_with_id(static_cast<uint32_t>(FieldNumber::DURATION), buffer, false);
      }

      return return_value;
    };

    ::EmbeddedProto::Error deserialize(::EmbeddedProto::ReadBufferInterface& buffer) override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;
      ::EmbeddedProto::WireFormatter::WireType wire_type = ::EmbeddedProto::WireFormatter::WireType::VARINT;
      uint32_t id_number = 0;
      FieldNumber id_tag = FieldNumber::NOT_SET;

      ::EmbeddedProto::Error tag_value = ::EmbeddedProto::WireFormatter::DeserializeTag(buffer, wire_type, id_number);
      while((::EmbeddedProto::Error::NO_ERRORS == return_value) && (::EmbeddedProto::Error::NO_ERRORS == tag_value))
      {
        id_tag = static_cast<FieldNumber>(id_number);
        switch(id_tag)
        {
          case FieldNumber::MESSAGE:
            return_value = message_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::PRIORITY:
            return_value = priority_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::DURATION:
            return_value = duration_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::NOT_SET:
            return_value = ::EmbeddedProto::Error::INVALID_FIELD_ID;
            break;

          default:
            return_value = skip_unknown_field(buffer, wire_type);
            break;
        }

        if(::EmbeddedProto::Error::NO_ERRORS == return_value)
        {
          // Read the next tag.
          tag_value = ::EmbeddedProto::WireFormatter::DeserializeTag(buffer, wire_type, id_number);
        }
      }

      // When an error was detect while reading the tag but no other errors where found, set it in the return value.
      if((::EmbeddedProto::Error::NO_ERRORS == return_value)
         && (::EmbeddedProto::Error::NO_ERRORS != tag_value)
         && (::EmbeddedProto::Error::END_OF_BUFFER != tag_value)) // The end of the buffer is not an array in this case.
      {
        return_value = tag_value;
      }

      return return_value;
    };

    void clear() override
    {
      clear_message();
      clear_priority();
      clear_duration();

    }

    static char const* field_number_to_name(const FieldNumber fieldNumber)
    {
      char const* name = nullptr;
      switch(fieldNumber)
      {
        case FieldNumber::MESSAGE:
          name = MESSAGE_NAME;
          break;
        case FieldNumber::PRIORITY:
          name = PRIORITY_NAME;
          break;
        case FieldNumber::DURATION:
          name = DURATION_NAME;
          break;
        default:
          name = "Invalid FieldNumber";
          break;
      }
      return name;
    }

#ifdef MSG_TO_STRING

    ::EmbeddedProto::string_view to_string(::EmbeddedProto::string_view& str) const
    {
      return this->to_string(str, 0, nullptr, true);
    }

    ::EmbeddedProto::string_view to_string(::EmbeddedProto::string_view& str, const uint32_t indent_level, char const* name, const bool first_field) const override
    {
      ::EmbeddedProto::string_view left_chars = str;
      int32_t n_chars_used = 0;

      if(!first_field)
      {
        // Add a comma behind the previous field.
        n_chars_used = snprintf(left_chars.data, left_chars.size, ",\n");
        if(0 < n_chars_used)
        {
          // Update the character pointer and characters left in the array.
          left_chars.data += n_chars_used;
          left_chars.size -= n_chars_used;
        }
      }

      if(nullptr != name)
      {
        if( 0 == indent_level)
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "\"%s\": {\n", name);
        }
        else
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "%*s\"%s\": {\n", indent_level, " ", name);
        }
      }
      else
      {
        if( 0 == indent_level)
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "{\n");
        }
        else
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "%*s{\n", indent_level, " ");
        }
      }
      
      if(0 < n_chars_used)
      {
        left_chars.data += n_chars_used;
        left_chars.size -= n_chars_used;
      }

      left_chars = message_.to_string(left_chars, indent_level + 2, MESSAGE_NAME, true);
      left_chars = priority_.to_string(left_chars, indent_level + 2, PRIORITY_NAME, false);
      left_chars = duration_.to_string(left_chars, indent_level + 2, DURATION_NAME, false);
  
      if( 0 == indent_level) 
      {
        n_chars_used = snprintf(left_chars.data, left_chars.size, "\n}");
      }
      else 
      {
        n_chars_used = snprintf(left_chars.data, left_chars.size, "\n%*s}", indent_level, " ");
      }

      if(0 < n_chars_used)
      {
        left_chars.data += n_chars_used;
        left_chars.size -= n_chars_used;
      }

      return left_chars;
    }

#endif // End of MSG_TO_STRING

  private:


      Message<SetMessagePacket_message_Message_data_LENGTH> message_;
      EmbeddedProto::uint32 priority_ = 0U;
      EmbeddedProto::uint32 duration_ = 0U;

};

} // End of namespace protocol
#endif // MESSAGES_H
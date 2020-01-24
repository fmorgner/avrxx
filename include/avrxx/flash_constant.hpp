#ifndef AVRXX_FLASH_CONSTANT_HPP
#define AVRXX_FLASH_CONSTANT_HPP

#include "avrxx/controller.hpp"

#include <cstdint>

namespace avr
  {

  enum struct flash_distance { near, far };

  template<typename Type, flash_distance Distance = flash_distance::near>
  struct [[gnu::progmem]] flash_constant
    {
    constexpr flash_constant(Type const value) : m_value{value} { }

    operator Type() const { return avr::mcu::read_program_memory<Type, Distance>(&m_value); }

    Type get() const { return static_cast<Type>(*this); }

    private:
      Type const m_value;
    };

  }

#endif

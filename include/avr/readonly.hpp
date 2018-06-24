#ifndef AVR_READONLY_HPP
#define AVR_READONLY_HPP

#include <avr/pgmspace.h>

namespace avr
  {

  template<typename Type>
  struct readonly
    {
    constexpr readonly(Type const value) : m_value{value} { }

    Type get() const { return reinterpret_cast<Type>(pgm_read_word_near(&m_value)); }

    private:
      Type const m_value;
    } __attribute__((__progmem__));

  }

#endif

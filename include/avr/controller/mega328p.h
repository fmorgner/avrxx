#ifndef AVR_CONTROLLER_MEGA328P_H
#define AVR_CONTROLLER_MEGA328P_H

#include "avr/register.hpp"
#include "avr/type_traits.hpp"
#include "avr/cstdint.hpp"

#include <avr/pgmspace.h>

namespace avr
  {

  struct mega328p
    {
    ~mega328p() = delete;

    using pinb = pin_register<0x23, 0b11111111>;
    using ddrb = ddr_register<0x24, 0b11111111>;
    using portb = port_register<0x25, 0b11111111>;

    using pinc = pin_register<0x26, 0b01111111>;
    using ddrc = ddr_register<0x27, 0b01111111>;
    using portc = port_register<0x28, 0b01111111>;

    using pind = pin_register<0x29, 0b11111111>;
    using ddrd = ddr_register<0x2a, 0b11111111>;
    using portd = port_register<0x2b, 0b11111111>;

    template<typename Type, auto>
    static auto read_program_memory(Type const * address) { return read_program_memory(address); }

    private:
      template<typename Type>
      static auto read_program_memory(Type const *)
        {
        static_assert(avr::deferred_failure<Type>{}, "Requested type is not supported for storage in program memory!");
        }
    };

    template<>
    inline auto mega328p::read_program_memory<avr::int8_t>(avr::int8_t const * address) { return pgm_read_byte_near(address); }

    template<>
    inline auto mega328p::read_program_memory<avr::uint8_t>(avr::uint8_t const * address) { return pgm_read_byte_near(address); }

    template<>
    inline auto mega328p::read_program_memory<avr::int16_t>(avr::int16_t const * address) { return pgm_read_word_near(address); }

    template<>
    inline auto mega328p::read_program_memory<avr::uint16_t>(avr::uint16_t const * address) { return pgm_read_word_near(address); }

    template<>
    inline auto mega328p::read_program_memory<avr::int32_t>(avr::int32_t const * address) { return pgm_read_dword_near(address); }

    template<>
    inline auto mega328p::read_program_memory<avr::uint32_t>(avr::uint32_t const * address) { return pgm_read_dword_near(address); }

    template<>
    inline auto mega328p::read_program_memory<float>(float const * address) { return pgm_read_float_near(address); }

  }

namespace avr { using mcu = ::avr::mega328p; }

#endif
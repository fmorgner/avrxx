#ifndef AVRXX_CONTROLLER_MEGA328P_HPP
#define AVRXX_CONTROLLER_MEGA328P_HPP

#include "avrxx/register.hpp"
#include "avrxx/meta.hpp"

#include <avr/pgmspace.h>

#include <cstdint>
#include <type_traits>

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

    using mcucr = rw_special_function_register<0x55, 8, 0b01110011>;

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
    inline auto mega328p::read_program_memory<std::int8_t>(std::int8_t const * address) { return pgm_read_byte_near(address); }

    template<>
    inline auto mega328p::read_program_memory<std::uint8_t>(std::uint8_t const * address) { return pgm_read_byte_near(address); }

    template<>
    inline auto mega328p::read_program_memory<std::int16_t>(std::int16_t const * address) { return pgm_read_word_near(address); }

    template<>
    inline auto mega328p::read_program_memory<std::uint16_t>(std::uint16_t const * address) { return pgm_read_word_near(address); }

    template<>
    inline auto mega328p::read_program_memory<std::int32_t>(std::int32_t const * address) { return pgm_read_dword_near(address); }

    template<>
    inline auto mega328p::read_program_memory<std::uint32_t>(std::uint32_t const * address) { return pgm_read_dword_near(address); }

    template<>
    inline auto mega328p::read_program_memory<float>(float const * address) { return pgm_read_float_near(address); }

    using mcu = ::avr::mega328p;
  }

#endif

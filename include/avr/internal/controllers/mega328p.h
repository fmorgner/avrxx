#ifndef AVR_INTERNAL_CONTROLLERS_MEGA328P_H
#define AVR_INTERNAL_CONTROLLERS_MEGA328P_H

#include "avr/internal/registers.hpp"
#include "atl/type_traits.hpp"
#include "atl/cstdint.hpp"

#include <avr/pgmspace.h>

namespace avr::internal::controllers
  {

  struct mega328p
    {
    ~mega328p() = delete;

    using pinb = registers::pin_register<0x23, 0b11111111>;
    using ddrb = registers::ddr_register<0x24, 0b11111111>;
    using portb = registers::port_register<0x25, 0b11111111>;

    using pinc = registers::pin_register<0x26, 0b01111111>;
    using ddrc = registers::ddr_register<0x27, 0b01111111>;
    using portc = registers::port_register<0x28, 0b01111111>;

    using pind = registers::pin_register<0x29, 0b11111111>;
    using ddrd = registers::ddr_register<0x2a, 0b11111111>;
    using portd = registers::port_register<0x2b, 0b11111111>;

    template<typename Type, auto>
    static auto read_program_memory(Type const * address) { return read_program_memory(address); }

    private:
      template<typename Type>
      static auto read_program_memory(Type const * address)
        {
        static_assert(atl::meta::deferred_failure<Type>{}, "Requested type is not supported for storage in program memory!");
        }
    };

    template<>
    inline auto mega328p::read_program_memory<atl::int8_t>(atl::int8_t const * address) { return pgm_read_byte_near(address); }

    template<>
    inline auto mega328p::read_program_memory<atl::uint8_t>(atl::uint8_t const * address) { return pgm_read_byte_near(address); }

    template<>
    inline auto mega328p::read_program_memory<atl::int16_t>(atl::int16_t const * address) { return pgm_read_word_near(address); }

    template<>
    inline auto mega328p::read_program_memory<atl::uint16_t>(atl::uint16_t const * address) { return pgm_read_word_near(address); }

    template<>
    inline auto mega328p::read_program_memory<atl::int32_t>(atl::int32_t const * address) { return pgm_read_dword_near(address); }

    template<>
    inline auto mega328p::read_program_memory<atl::uint32_t>(atl::uint32_t const * address) { return pgm_read_dword_near(address); }

    template<>
    inline auto mega328p::read_program_memory<float>(float const * address) { return pgm_read_float_near(address); }

  }

namespace avr { using mcu = avr::internal::controllers::mega328p; }

#endif

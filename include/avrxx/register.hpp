#ifndef AVRXX_REGISTER_HPP
#define AVRXX_REGISTER_HPP

#include "avrxx/meta.hpp"
#include "avrxx/int_types.hpp"

#include <cstddef>

namespace avr
  {

  template<std::ptrdiff_t Address,
           std::uint8_t Bits,
           avr::uint_for_size_t<Bits> ValidBits>
  class special_function_register
    {
    static_assert(
      avr::in_range(Address, 0x20, 0xff),
      "Address is not in Special Function Register range [0x20, 0xff]"
    );

    special_function_register() = delete;
    special_function_register(special_function_register const &) = delete;
    special_function_register(special_function_register &&) = delete;
    ~special_function_register() = delete;

    special_function_register & operator=(special_function_register const &) = delete;
    special_function_register & operator=(special_function_register &&) = delete;

    protected:
      static auto constexpr address = Address;
      static auto constexpr bits = Bits;
      static auto constexpr valid_bits = ValidBits;

      static decltype(auto) reg() { return (*reinterpret_cast<value_type volatile *>(address)); };

    public:
      using value_type = avr::uint_for_size_t<Bits>;

      static avr::uint_for_size_t<bits> get()
      {
        return reg();
      }

      static bool get_bit_unsafe(std::uint8_t const bit) { return !!(reg() & (1 << bit)); }

      template<std::uint8_t Bit>
      static auto get_bit()
        {
        static_assert(valid_bits & (1 << Bit), "Bit index is invalid!");
        return get_bit_unsafe(Bit);
        }
    };

  template<std::ptrdiff_t Address,
           std::uint8_t Bits,
           avr::uint_for_size_t<Bits> ValidBits>
  class rw_special_function_register : public special_function_register<Address, Bits, ValidBits>
    {
    protected:
      using special_function_register<Address, Bits, ValidBits>::reg;
      using special_function_register<Address, Bits, ValidBits>::valid_bits;
      using typename special_function_register<Address, Bits, ValidBits>::value_type;

    public:
      static auto set(value_type const value) { reg() = value; }

      static auto set_bit_unsafe(std::uint8_t bit) { reg() |= 1 << bit; }

      template<uint8_t Bit>
      static auto set_bit()
        {
        static_assert(valid_bits & (1 << Bit), "Bit index is invalid!");
        set_bit_unsafe(Bit);
        }
    };

  template<std::ptrdiff_t Address,
           avr::uint_for_size_t<8> Bits,
           avr::uint_for_size_t<Bits> ValidBits>
  using ro_special_function_register = special_function_register<Address, Bits, ValidBits>;

  template<std::ptrdiff_t Address,
           std::uint8_t Bits,
           avr::uint_for_size_t<Bits> ValidBits>
  using rw_io_register = rw_special_function_register<Address, Bits, ValidBits>;

  template<std::ptrdiff_t Address,
           std::uint8_t Bits,
           avr::uint_for_size_t<Bits> ValidBits>
  using ro_io_register = ro_special_function_register<Address, Bits, ValidBits>;

  template<std::ptrdiff_t Address,
           std::uint8_t ValidPins>
  struct pin_register
    {
    using base_type = ro_io_register<Address, 8, ValidPins>;

    static auto get() { return base_type::get(); }
    static auto get_pin_unsafe(std::uint8_t pin) { return base_type::get_bit_unsafe(pin); }
    template<std::uint8_t Pin>
    static auto get_pin() { return base_type::template get_bit<Pin>(); }
    };

  template<std::ptrdiff_t Address, avr::uint_for_size_t<8> ValidBits>
  struct ddr_register
    {
    using base_type = rw_io_register<Address, 8, ValidBits>;

    enum struct direction : bool
      {
      in,
      out
      };

    static auto get() { return base_type::get(); }
    static auto get_direction_unsafe(std::uint8_t bit) { return direction{base_type::get_bit_unsafe(bit)}; }
    template<std::uint8_t Bit>
    static auto get_direction() { return direction{base_type::template get_bit<Bit>()}; }

    static auto set(decltype(ValidBits) value) { base_type::set(value); }
    static auto set_direction_unsafe(direction direction) { base_type::set_bit_unsafe(); }
    };

  template<std::ptrdiff_t Address, avr::uint_for_size_t<8> ValidBits>
  using port_register = rw_io_register<Address, 8, ValidBits>;
  }

#endif

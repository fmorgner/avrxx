#ifndef AVR_INTERNAL_REGISTERS_HPP
#define AVR_INTERNAL_REGISTERS_HPP

#include "atl/meta.hpp"
#include "atl/int_types.hpp"

#include <stddef.h>

/**
 * @internal
 * @brief The <i>Special Function Register</i> infrastructure
 */
namespace avr::internal::registers
  {

  /**
   * @brief A safe wrapper for AVR <b>Special Function Registers</b>
   *
   * This class provides a safe and zero-cost abstraction for the Spcial Purpose Registers found in AVR microcontrollers. All
   * accesses to a register as well as its bits are bound checked, and violations of these bounds will cause compilation to
   * fail.
   *
   * @tparam Address The register's address in memory
   * @tparam Base The address base of the register
   * @tparam Bits The register's size in Bits
   */
  template<ptrdiff_t Address, ptrdiff_t Base = 0x20, uint8_t Bits = 8>
  class special_function_register
    {
    /**
     * @brief A safe wrapper for a single bit of a register
     *
     * This class provides bounds safe access to single bits in a register. It also provides functions to set, clea), get, and
     * toggle the selected bit. If an bit index outside of the registers range is selected, compilation will fail.
     *
     * @tparam Index The 0-based index of the bit inside the register.
     */
    template<uint8_t Index>
    struct bit_wrapper
      {
      static_assert(Index <= Bits - 1, "Bit address is outside of register");

      /**
       * @brief Set the bit
       */
      static auto constexpr set()
        {
        reg() |= 1 << Index;
        }

      /**
       * @brief Clear the bit
       */
      static auto constexpr clear()
        {
        reg() &= ~(1 << Index);
        }

      /**
       * @brief Retrieve the bit's current value
       */
      static auto constexpr get()
        {
        return reg() & (1 << Index);
        }

      /**
       * @brief Toggle the bit's value
       */
      static auto constexpr toggle()
        {
        reg() ^= 1 << Index;
        }
      };

    /**
     * @internal
     * @brief Retrieve a referene to the underlying memory location
     */
    static decltype(auto) constexpr reg()
      {
      return (*reinterpret_cast<value_type volatile *>(address));
      };

    public:
      /**
       * @brief The register's type
       *
       * This type alias provides the type of the underlying register
       */
      using value_type = atl::int_types::uint_for_size_t<Bits>;

      /**
       * @brief The register's effective address
       */
      static auto constexpr address = Base + Address;

      static_assert(atl::meta::in_range(address, 0x20, 0xff), "Address is not in Special Function Register range [0x20, 0xff]");

      /**
       * @brief Set the value of the complete register
       *
       * Contrary to single-bit modifications via #bit, this functions can be used to set the value of the whole register by
       * writing the register's full content.
       *
       * @see #get()
       */
      static auto constexpr set(value_type const value)
        {
        reg() = value;
        }

      /**
       * @brief Get the full contents of the register
       *
       * This function enables the retrieval of the full contents of the underlying register.
       *
       * @see #set()
       */
      static auto constexpr get()
        {
        return reg();
        }

      /**
       * @brief Interface with a single register bit
       *
       * This template variable provides access to each bit of a register separately. This object can be used to manipulate
       * single bits in a register.
       */
      template<uint8_t Index>
      static auto constexpr bit = bit_wrapper<Index>{};
    };

  /**
   * @brief A safe register wrapper to access the I/O registers of an AVR microcontroller
   *
   * This class provides access to the I/O register of an AVR microcontroller. It ensures that only addresses within the I/O
   * address space of the device are used as I/O registers.
   */
  template<ptrdiff_t Address, size_t Bits>
  struct io_register : special_function_register<Address, 0x20, Bits>
    {
    using special_function_register<Address, 0x20, Bits>::address;

    static_assert(atl::meta::in_range(address, 0x20, 0x5f), "Address is not in I/O register range");
    };

  /**
   * @brief A convenience variable template to access 8-bit I/O registers
   */
  template<ptrdiff_t Address>
  auto constexpr io_register_8 = io_register<Address, 8>{};
  }

#endif

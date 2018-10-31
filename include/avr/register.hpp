#ifndef AVR_REGISTER_HPP
#define AVR_REGISTER_HPP

#include "avr/meta.hpp"
#include "avr/int_types.hpp"
#include "avr/cstddef.hpp"

/**
 * @file
 * @internal
 * @brief The <i>Special Function Register</i> infrastructure
 *
 * @since 1.0.0
 */

namespace avr
  {

  /**
   * @brief A safe wrapper for AVR <b>Special Function Registers</b>
   *
   * This class provides a safe and zero-cost abstraction for the Spcial
   * Purpose Registers found in AVR microcontrollers. All accesses to a
   * register as well as its bits are bound checked, and violations of these
   * bounds will cause compilation to fail.
   *
   * @tparam Address The register's address in memory
   * @tparam Base The address base of the register
   * @tparam Bits The register's size in Bits
   * @tparam ValidBits The available bits in the register
   * @tparam EffectiveAddress The actual address of the register in memory space
   *
   * @since 1.0.0
   */
  template<avr::ptrdiff_t Address,
           avr::uint_for_size_t<8> Bits,
           avr::uint_for_size_t<Bits> ValidBits>
  class special_function_register
    {
    static_assert(avr::in_range(Address, 0x20, 0xff),
                  "Address is not in Special Function Register range [0x20, 0xff]");

    special_function_register() = delete;
    special_function_register(special_function_register const &) = delete;
    special_function_register(special_function_register &&) = delete;
    ~special_function_register() = delete;

    special_function_register & operator=(special_function_register const &) = delete;
    special_function_register & operator=(special_function_register &&) = delete;

    protected:
      /**
       * @internal
       * The effective register address in memory space
       */
      static auto constexpr address = Address;

      /**
       * @internal
       * The bitwidth of this register
       */
      static auto constexpr bits = Bits;

      /**
       * @internal
       * A bitmap describing the accessible bits of this register
       */
      static auto constexpr valid_bits = ValidBits;

      /**
       * @internal
       * @brief Retrieve a referene to the underlying memory location
       */
      static decltype(auto) reg() { return (*reinterpret_cast<value_type volatile *>(address)); };

    public:
      /**
       * @brief The register's type
       *
       * This type alias provides the type of the underlying register
       */
      using value_type = avr::uint_for_size_t<Bits>;

      /**
       * @brief Get the full contents of the register
       *
       * This function enables the retrieval of the full contents of the underlying register.
       *
       * @see avr::rw_special_function_register::set
       */
      static auto get() { return reg(); }

      static auto get_bit(avr::uint8_t const bit) { return !!(reg() & (1 << bit)); }

      template<avr::uint8_t Bit>
      static auto get_bit()
        {
        static_assert(valid_bits & (1 << Bit), "Bit index is invalid!");
        return get_bit(Bit);
        }
    };

  /**
   * @brief A safe wrapper for writable AVR <b>Special Function Registers</b>
   *
   * This class provides a safe and zero-cost abstraction for the Spcial Purpose Registers found in AVR microcontrollers. All
   * accesses to a register as well as its bits are bound checked, and violations of these bounds will cause compilation to
   * fail.
   *
   * @tparam Address The register's address in memory
   * @tparam Base The address base of the register
   * @tparam Bits The register's size in Bits
   * @tparam ValidBits The available bits in the register
   *
   * @since 1.0.0
   */
  template<avr::ptrdiff_t Address,
           avr::uint_for_size_t<8> Bits,
           avr::uint_for_size_t<Bits> ValidBits>
  class rw_special_function_register : public special_function_register<Address, Bits, ValidBits>
    {
    protected:
      using special_function_register<Address, Bits, ValidBits>::reg;
      using special_function_register<Address, Bits, ValidBits>::valid_bits;
      using typename special_function_register<Address, Bits, ValidBits>::value_type;

    public:
      /**
       * @brief Set the value of the complete register
       *
       * Contrary to single-bit modifications via avr::bit, this functions can be used to set the value of
       * the whole register by writing the register's full content.
       *
       * @see avr::special_function_register::get
       */
      static auto set(value_type const value) { reg() = value; }

      static auto set_bit_unsafe(uint8_t const bit) { reg() |= 1 << bit; }

      template<uint8_t Bit>
      static auto set_bit()
        {
        static_assert(valid_bits & (1 << Bit), "Bit index is invalid!");
        set_bit_unsafe(Bit);
        }
    };

  /**
   * @brief A safe wrapper for read-only AVR <b>Special Function Registers</b>
   *
   * This class provides a safe and zero-cost abstraction for the Spcial Purpose Registers found in AVR microcontrollers. All
   * accesses to a register as well as its bits are bound checked, and violations of these bounds will cause compilation to
   * fail.
   *
   * @tparam Address The register's address in memory
   * @tparam Base The address base of the register
   * @tparam Bits The register's size in Bits
   * @tparam ValidBits The available bits in the register
   *
   * @since 1.0.0
   */
  template<avr::ptrdiff_t Address,
           avr::uint_for_size_t<8> Bits,
           avr::uint_for_size_t<Bits> ValidBits>
  using ro_special_function_register = special_function_register<Address, Bits, ValidBits>;

  /**
   * @brief A safe register wrapper to access the I/O registers of an AVR microcontroller
   *
   * This class provides access to the I/O register of an AVR microcontroller. It ensures that only addresses within the I/O
   * address space of the device are used as I/O registers.
   *
   * @tparam Address The register's address in memory
   * @tparam Bits The size of register in bits
   * @tparam ValidBits The available bits in the register
   *
   * @since 1.0.0
   */
  template<avr::ptrdiff_t Address, avr::uint_for_size_t<8> Bits, avr::uint_for_size_t<Bits> ValidBits>
  struct rw_io_register : rw_special_function_register<Address, Bits, ValidBits> { };

  /**
   * @brief A safe register wrapper to access the I/O registers of an AVR microcontroller
   *
   * This class provides access to the I/O register of an AVR microcontroller. It ensures that only addresses within the I/O
   * address space of the device are used as I/O registers.
   *
   * @tparam Address The register's address in memory
   * @tparam Bits The size of register in bits
   * @tparam ValidBits The available bits in the register
   *
   * @since 1.0.0
   */
  template<avr::ptrdiff_t Address, avr::uint_for_size_t<8> Bits, avr::uint_for_size_t<Bits> ValidBits>
  struct ro_io_register : ro_special_function_register<Address, Bits, ValidBits> { };

  /**
   * @brief A safe wrapper for PINx registers of an AVR microcontroller
   *
   * This class provides access to the PINx registers of an AVR microcontroller. It provides a member type <code>pin</code>
   * to access a specific pin in the register.
   *
   * @tparam Address The register's address in memory
   * @tparam ValidBits The available bits in the register
   *
   * @since 1.0.0
   */
  template<avr::ptrdiff_t Address, avr::uint_for_size_t<8> ValidBits>
  using pin_register = ro_io_register<Address, 8, ValidBits>;

  /**
   * @brief A safe wrapper for DDRx registers of an AVR microcontroller
   *
   * This class provides access to the DDRx registers of an AVR microcontroller. It provides a member type <code>ddr</code>
   * to access ddr bit for a specific ddr-bit in the register.
   *
   * @tparam Address The register's address in memory
   * @tparam ValidBits The available bits in the register
   *
   * @since 1.0.0
   */
  template<avr::ptrdiff_t Address, avr::uint_for_size_t<8> ValidBits>
  using ddr_register = rw_io_register<Address, 8, ValidBits>;

  /**
   * @brief A safe wrapper for PORTx registers of an AVR microcontroller
   *
   * This class provides access to the PORTx registers of an AVR microcontroller. It provides a member type <code>port</code> to
   * access a specific port-bit in the register.
   *
   * @tparam Address The register's address in memory
   * @tparam ValidBits The available bits in the register
   *
   * @since 1.0.0
   */
  template<avr::ptrdiff_t Address, avr::uint_for_size_t<8> ValidBits>
  using port_register = rw_io_register<Address, 8, ValidBits>;
  }

#endif

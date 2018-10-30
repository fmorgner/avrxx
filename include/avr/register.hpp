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

  enum struct bit : avr::uint8_t { zero, one, two, three, four, five, six, seven };
  enum struct pin : avr::uint8_t { zero, one, two, three, four, five, six, seven };

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
           avr::uint8_t Bits,
           avr::uint_for_size_t<Bits> ValidBits,
           typename BitAccessType = avr::uint8_t>
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
       * The type used to access individual bits of this register
       */
      using bit_access_type = BitAccessType;

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

      static auto get_bit_unsafe(bit_access_type const bit) { return !!(reg() & (1 << static_cast<decltype(valid_bits)>(bit))); }

      template<bit_access_type Bit>
      static auto get_bit()
        {
        static_assert(valid_bits & (1 << static_cast<decltype(valid_bits)>(Bit)), "Bit index is invalid!");
        return get_bit_unsafe(Bit);
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
           avr::uint8_t Bits,
           avr::uint_for_size_t<Bits> ValidBits,
           typename BitAccessType = avr::uint8_t>
  class rw_special_function_register : public special_function_register<Address, Bits, ValidBits, BitAccessType>
    {
    protected:
      using special_function_register<Address, Bits, ValidBits, BitAccessType>::reg;
      using special_function_register<Address, Bits, ValidBits, BitAccessType>::valid_bits;
      using typename special_function_register<Address, Bits, ValidBits, BitAccessType>::value_type;
      using typename special_function_register<Address, Bits, ValidBits, BitAccessType>::bit_access_type;

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

      static auto set_bit_unsafe(bit_access_type const bit) { reg() |= 1 << static_cast<decltype(valid_bits)>(bit); }

      template<bit_access_type Bit>
      static auto set_bit()
        {
        static_assert(valid_bits & (1 << static_cast<decltype(valid_bits)>(Bit)), "Bit index is invalid!");
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
           avr::uint_for_size_t<Bits> ValidBits,
           typename BitAccessType>
  using ro_special_function_register = special_function_register<Address, Bits, ValidBits, BitAccessType>;

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
  template<avr::ptrdiff_t Address,
           avr::uint8_t Bits,
           avr::uint_for_size_t<Bits> ValidBits,
           typename BitAccessType>
  using rw_io_register = rw_special_function_register<Address, Bits, ValidBits, BitAccessType>;

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
  template<avr::ptrdiff_t Address,
           avr::uint8_t Bits,
           avr::uint_for_size_t<Bits> ValidBits,
           typename BitAccessType>
  using ro_io_register = ro_special_function_register<Address, Bits, ValidBits, BitAccessType>;

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
  template<avr::ptrdiff_t Address,
           avr::uint8_t ValidPins>
  struct pin_register
    {
    using base_type = ro_io_register<Address, 8, ValidPins, avr::pin>;

    static auto get() { return base_type::get(); }
    static auto get_unsafe(pin const pin) { return base_type::get_bit_unsafe(pin); }
    template<avr::pin Pin>
    static auto get() { return base_type::template get_bit<Pin>(); }
    };

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
  using ddr_register = rw_io_register<Address, 8, ValidBits, avr::bit>;

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
  using port_register = rw_io_register<Address, 8, ValidBits, avr::bit>;
  }

#endif

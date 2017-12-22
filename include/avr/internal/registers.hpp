#ifndef AVR_INTERNAL_REGISTERS_HPP
#define AVR_INTERNAL_REGISTERS_HPP

#include "atl/meta.hpp"
#include "atl/int_types.hpp"
#include "atl/cstddef.hpp"

/**
 * @internal
 * @brief The <i>Special Function Register</i> infrastructure
 */
namespace avr::internal::registers
  {

  template<typename Register, atl::int_types::uint_for_size_t<8> Index>
  struct bit
    {
    static_assert(Index <= Register::bits - 1, "Bit address is outside of register");
    static_assert(Register::validBits & (1 << Index), "Bit is reserved");

    bit() = delete;
    bit(bit const &) = delete;
    bit(bit &&) = delete;

    ~bit() = delete;

    bit & operator=(bit const &) = delete;
    bit & operator=(bit &&) = delete;

    /**
     * @brief Retrieve the bit's current value
     */
    static bool constexpr get()
      {
      return Register::special_function_register::reg() & (1 << Index);
      }
    };

  /**
   * @brief A safe wrapper for a single read-write bit of a register
   *
   * This class provides bounds safe access to single bits in a register. It also provides functions to set, clear, get, and
   * toggle the selected bit. If an bit index outside of the registers range is selected, compilation will fail.
   *
   * @tparam Index The 0-based index of the bit inside the register.
   */
  template<typename Register, atl::int_types::uint_for_size_t<8> Index>
  struct rw_bit : bit<Register, Index>
    {
    /**
     * @brief Set the bit
     */
    static void constexpr set()
      {
      Register::special_function_register::reg() |= 1 << Index;
      }

    /**
     * @brief Clear the bit
     */
    static void constexpr clear()
      {
      Register::special_function_register::reg() &= ~(1 << Index);
      }

    /**
     * @brief Toggle the bit's value
     */
    static void constexpr toggle()
      {
      Register::special_function_register::reg() ^= 1 << Index;
      }
    };

  /**
   * @brief A safe wrapper for a single read-only bit of a register
   *
   * This class provides bounds safe access to single bits in a register. It also provides a function to get the selected bit.
   * If an bit index outside of the registers range is selected, compilation will fail.
   *
   * @tparam Index The 0-based index of the bit inside the register.
   */
  template<typename Register, atl::int_types::uint_for_size_t<8> Index>
  struct ro_bit : bit<Register, Index> { };

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
   * @tparam ValidBits The available bits in the register
   */
  template<atl::ptrdiff_t Address,
           atl::ptrdiff_t Base,
           atl::int_types::uint_for_size_t<8> Bits,
           atl::int_types::uint_for_size_t<Bits> ValidBits,
           atl::ptrdiff_t EffectiveAddress = Base + Address>
  class special_function_register
    {
    static_assert(atl::meta::in_range(EffectiveAddress, 0x20, 0xff),
                  "Address is not in Special Function Register range [0x20, 0xff]");

    special_function_register() = delete;
    special_function_register(special_function_register const &) = delete;
    special_function_register(special_function_register &&) = delete;

    ~special_function_register() = delete;

    special_function_register & operator=(special_function_register const &) = delete;
    special_function_register & operator=(special_function_register &&) = delete;

    template<typename Register, decltype(ValidBits) PinNumber>
    friend struct bit;

    template<typename Register, decltype(ValidBits) PinNumber>
    friend struct rw_bit;

    template<typename Register, decltype(ValidBits) PinNumber>
    friend struct ro_bit;

    protected:
      static auto constexpr address = EffectiveAddress;
      static auto constexpr bits = Bits;
      static auto constexpr validBits = ValidBits;

      /**
       * @internal
       * @brief Retrieve a referene to the underlying memory location
       */
      static decltype(auto) constexpr reg()
        {
        return (*reinterpret_cast<value_type volatile *>(EffectiveAddress));
        };

    public:
      /**
       * @brief The register's type
       *
       * This type alias provides the type of the underlying register
       */
      using value_type = atl::int_types::uint_for_size_t<Bits>;

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
    };

  template<atl::ptrdiff_t Address,
           atl::ptrdiff_t Base,
           atl::int_types::uint_for_size_t<8> Bits,
           atl::int_types::uint_for_size_t<Bits> ValidBits>
  class rw_special_function_register : public special_function_register<Address, Base, Bits, ValidBits>
    {
    protected:
      template<uint16_t BitIndex>
      using bit = rw_bit<rw_special_function_register, BitIndex>;

      using special_function_register<Address, Base, Bits, ValidBits>::reg;
      using typename special_function_register<Address, Base, Bits, ValidBits>::value_type;

    public:
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
    };

  template<atl::ptrdiff_t Address,
           atl::ptrdiff_t Base,
           atl::int_types::uint_for_size_t<8> Bits,
           atl::int_types::uint_for_size_t<Bits> ValidBits>
  class ro_special_function_register : public special_function_register<Address, Base, Bits, ValidBits>
    {
    static_assert(atl::meta::in_range(special_function_register<Address, 0x20, Bits, ValidBits>::address, 0x20, 0x5f),
                  "Address is not in I/O register range");

    protected:
      template<uint16_t BitIndex>
      using bit = ro_bit<ro_special_function_register, BitIndex>;
    };

  /**
   * @brief A safe register wrapper to access the I/O registers of an AVR microcontroller
   *
   * This class provides access to the I/O register of an AVR microcontroller. It ensures that only addresses within the I/O
   * address space of the device are used as I/O registers.
   *
   * @tparam Address The register's address in memory
   * @tparam Bits The size of register in bits
   * @tparam ValidBits The available bits in the register
   */
  template<atl::ptrdiff_t Address, atl::int_types::uint_for_size_t<8> Bits, atl::int_types::uint_for_size_t<Bits> ValidBits>
  struct rw_io_register : rw_special_function_register<Address, 0x20, Bits, ValidBits> { };

  /**
   * @brief A safe register wrapper to access the I/O registers of an AVR microcontroller
   *
   * This class provides access to the I/O register of an AVR microcontroller. It ensures that only addresses within the I/O
   * address space of the device are used as I/O registers.
   *
   * @tparam Address The register's address in memory
   * @tparam Bits The size of register in bits
   * @tparam ValidBits The available bits in the register
   */
  template<atl::ptrdiff_t Address, atl::int_types::uint_for_size_t<8> Bits, atl::int_types::uint_for_size_t<Bits> ValidBits>
  struct ro_io_register : ro_special_function_register<Address, 0x20, Bits, ValidBits> { };

  /**
   * @brief A safe wrapper for PINx registers of an AVR microcontroller
   *
   * This class provides access to the PINx registers of an AVR microcontroller. It provides a member type #pin to access a
   * specific pin in the register.
   *
   * @tparam Address The register's address in memory
   * @tparam ValidBits The available bits in the register
   */
  template<atl::ptrdiff_t Address, atl::int_types::uint_for_size_t<8> ValidBits>
  struct pin_register : ro_io_register<Address, 8, ValidBits>
    {
    template<uint8_t PinNumber>
    using pin = typename ro_io_register<Address, 8, ValidBits>::template bit<PinNumber>;
    };

  /**
   * @brief A safe wrapper for DDRx registers of an AVR microcontroller
   *
   * This class provides access to the DDRx registers of an AVR microcontroller. It provides a member type #ddr to access ddr
   * bit for a specific pin in the register.
   *
   * @tparam Address The register's address in memory
   * @tparam ValidBits The available bits in the register
   */
  template<atl::ptrdiff_t Address, atl::int_types::uint_for_size_t<8> ValidBits>
  struct ddr_register : rw_io_register<Address, 8, ValidBits>
    {
    template<uint8_t DDRNumber>
    using ddr = typename rw_io_register<Address, 8, ValidBits>::template bit<DDRNumber>;
    };

  /**
   * @brief A safe wrapper for PINx registers of an AVR microcontroller
   *
   * This class provides access to the PINx registers of an AVR microcontroller. It provides a member type #pin to access a
   * specific pin in the register.
   *
   * @tparam Address The register's address in memory
   * @tparam ValidBits The available bits in the register
   */
  template<atl::ptrdiff_t Address, atl::int_types::uint_for_size_t<8> ValidBits>
  struct port_register : rw_io_register<Address, 8, ValidBits>
    {
    template<uint8_t PortNumber>
    using port = typename rw_io_register<Address, 8, ValidBits>::template bit<PortNumber>;
    };
  }

#endif

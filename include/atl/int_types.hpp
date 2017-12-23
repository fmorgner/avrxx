#ifndef ATL_INT_TYPES_HPP
#define ATL_INT_TYPES_HPP

#include "atl/type_traits.hpp"
#include "atl/cstdint.hpp"

/**
 * @file
 * @brief The integer type library
 *
 * @since 1.0.0
 */

namespace atl::int_types
  {

  /**
   * @brief A template to determine the exact int type to represent the given size
   *
   * This template provides integer types that match the given size exactly. If a given size can be represented exaclty, it
   * provides a member type called @p type that is an alias for the repective integer type.
   *
   * @tparam Size The desired size of the type
   *
   * @see #atl::int_types::uint_for_size For the equivalent helper for unsigned types
   *
   * @since 1.0.0
   */
  template<int Size>
  struct int_for_size;

  /**
   * @brief Specialization of atl::int_types::int_for_size for 8 bit integers
   *
   * @since 1.0.0
   */
  template<>
  struct int_for_size<8>
    {
    /**
     * The actual integer type
     */
    using type = int8_t;
    };

  /**
   * @brief Specialization of atl::int_types::int_for_size for 16 bit integers
   *
   * @since 1.0.0
   */
  template<>
  struct int_for_size<16>
    {
    /**
     * The actual integer type
     */
    using type = int16_t;
    };

  /**
   * @brief Specialization of atl::int_types::int_for_size for 32 bit integers
   *
   * @since 1.0.0
   */
  template<>
  struct int_for_size<32>
    {
    /**
     * The actual integer type
     */
    using type = int32_t;
    };

  /**
   * @brief Specialization of atl::int_types::int_for_size for 64 bit integers
   *
   * @since 1.0.0
   */
  template<>
  struct int_for_size<64>
    {
    /**
     * The actual integer type
     */
    using type = int64_t;
    };

  /**
   * @brief Convenience alias for the @p type member of atl::int_types::int_for_size
   *
   * @tparam Size The desired size of the type
   *
   * @since 1.0.0
   */
  template<int Size>
  using int_for_size_t = typename int_for_size<Size>::type;

  /**
   * @brief A template to determine the exact unsigned int type to represent the given size
   *
   * This template provides unsigned integer types that match the given size exactly. If a given size can be represented
   * exaclty, it provides a member type called @p type that is an alias for the repective integer type.
   *
   * @tparam Size The desired size of the type
   *
   * @see #atl::int_types::int_for_size For the equivalent helper for signed types
   *
   * @since 1.0.0
   */
  template<int Size>
  struct uint_for_size : make_unsigned<int_for_size_t<Size>> { };

  /**
   * @brief Convenience alias for the @p type member of atl::int_types::uint_for_size
   *
   * @tparam Size The desired size of the type
   *
   * @since 1.0.0
   */
  template<int Size>
  using uint_for_size_t = typename uint_for_size<Size>::type;

  }

#endif

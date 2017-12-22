#ifndef ATL_INT_TYPES_HPP
#define ATL_INT_TYPES_HPP

#include "atl/type_traits.hpp"
#include "atl/cstdint.hpp"

/**
 * @brief The integer type library
 */
namespace atl::int_types
  {

  /**
   * @brief A template to determine the exact int type to represent the given size
   *
   * This template provides integer types that match the given size exactly. If a given size can be represented exaclty, it
   * provides a member type called @p type that is an alias for the repective integer type.
   */
  template<int>
  struct int_for_size;

  template<>
  struct int_for_size<8>  { using type = int8_t; };

  template<>
  struct int_for_size<16> { using type = int16_t; };

  template<>
  struct int_for_size<32> { using type = int32_t; };

  template<>
  struct int_for_size<64> { using type = int64_t; };

  /**
   * @brief Conveniance alias for the @p type member of atl::int_types::int_for_size<Size>
   */
  template<int Size>
  using int_for_size_t = typename int_for_size<Size>::type;

  template<int Size>
  using uint_for_size = make_unsigned<int_for_size_t<Size>>;

  template<int Size>
  using uint_for_size_t = typename uint_for_size<Size>::type;

  }

#endif

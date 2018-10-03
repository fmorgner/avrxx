#ifndef ATL_META_HPP
#define ATL_META_HPP

#include "atl/type_traits.hpp"

/**
 * @file
 * @brief The <i>Template Meta-Programming Library</i>
 *
 * @since 1.0.0
 */

namespace atl::meta
  {

  /**
   * @brief Check if a given value is in a speific range
   *
   * @param value The value to check
   * @param low The lower bound (inclusive)
   * @param high The upper bound (inclusive)
   *
   * @since 1.0.0
   */
  template<typename ValueType>
  constexpr auto in_range(ValueType value, ValueType low, ValueType high) { return value >= low && value <= high; }

  template<typename ...>
  using deferred_failure = atl::false_type;

  }

#endif

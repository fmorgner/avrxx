#ifndef AVRXX_META_HPP
#define AVRXX_META_HPP

#include <type_traits>

namespace avr
  {

  template<typename ValueType>
  constexpr auto in_range(ValueType value, ValueType low, ValueType high) { return value >= low && value <= high; }

  template<typename ...>
  using deferred_failure = std::false_type;

  }

#endif

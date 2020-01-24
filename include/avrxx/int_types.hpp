#ifndef AVRXX_INT_TYPES_HPP
#define AVRXX_INT_TYPES_HPP

#include <cstdint>
#include <type_traits>

namespace avr
  {

  template<int Size>
  struct int_for_size;

  template<>
  struct int_for_size<8>
    {
    using type = std::int8_t;
    };

  template<>
  struct int_for_size<16>
    {
    using type = std::int16_t;
    };

  template<>
  struct int_for_size<32>
    {
    using type = std::int32_t;
    };

  template<>
  struct int_for_size<64>
    {
    using type = std::int64_t;
    };

  template<int Size>
  using int_for_size_t = typename int_for_size<Size>::type;

  template<int Size>
  struct uint_for_size : std::make_unsigned<int_for_size_t<Size>> { };

  template<int Size>
  using uint_for_size_t = typename uint_for_size<Size>::type;

  }

#endif

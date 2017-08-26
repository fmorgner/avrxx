#ifndef ATL_INT_TYPES_HPP
#define ATL_INT_TYPES_HPP

#include <stdint.h>

namespace atl::int_types
  {

  template<int>
  struct uint_for_size;

  template<>
  struct uint_for_size<8>  { using type = uint8_t; };

  template<>
  struct uint_for_size<16> { using type = uint16_t; };

  template<>
  struct uint_for_size<32> { using type = uint32_t; };

  template<>
  struct uint_for_size<64> { using type = uint64_t; };

  template<int Size>
  using uint_for_size_t = typename uint_for_size<Size>::type;

  }

#endif

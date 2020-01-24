#ifndef AVRXX_STRING_UTIL_HPP
#define AVRXX_STRING_UTIL_HPP

#include <cstddef>

namespace avr
  {

  constexpr size_t length(char const * const string)
    {
    size_t pos{};
    for(; string[pos] != '\0'; ++pos) ;
    return pos;
    }

  namespace internal::test
    {
    static_assert(0 == length(""));
    static_assert(4 == length("ASDF"));
    static_assert(0 == length("\0ASDF"));
    static_assert(2 == length("AS\0DF"));
    }

  }

#endif

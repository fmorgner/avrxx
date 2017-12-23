#ifndef ATL_STRING_UTIL_HPP
#define ATL_STRING_UTIL_HPP

#include <stddef.h>

/**
 * @file
 * @brief The <i>String Utility</i> library
 *
 * @since 1.0.0
 */

namespace atl::string
  {

  /**
   * @brief Calculate the length of a string
   *
   * This function calculates the length of a given C-style string. The string <b>MUST</b> be terminated by a @c NULL byte. The
   * length of a string is calculated <b>without</b> the trailing @c NULL character, so the length of the string "ABCD" is 4.
   *
   * @pre @c string ≠ @c nullptr
   * @pre ∃n∈ℕ <code>string[n]</code> ＝ @c NULL
   * @post *return_value* ≥ 0
   *
   * @param string A C-style string
   * @returns The length of @p string
   *
   * @since 1.0.0
   */
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

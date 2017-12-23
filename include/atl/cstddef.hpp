#ifndef ATL_CSTDDEF_HPP
#define ATL_CSTDDEF_HPP

/**
 * @file
 * @brief Standard type definitions
 *
 * @since 1.0.0
 */

namespace atl
  {

  /**
   * An signed integer type to be used in pointer arithmetic
   *
   * @since 1.0.0
   */
#ifdef __DOXYGEN__
  using ptrdiff_t = implementation_defined;
#else
  using ptrdiff_t = __PTRDIFF_TYPE__;
#endif

  /**
   * An unsigned integer type to represent object sizes
   *
   * @since 1.0.0
   */
#ifdef __DOXYGEN__
  using size_t = implementation_defined;
#else
  using size_t = __SIZE_TYPE__;
#endif

  }

#endif

#ifndef ATL_CSTDINT_HPP
#define ATL_CSTDINT_HPP

/**
 * @file
 * @brief Standard integer types
 *
 * @since 1.0.0
 */

namespace atl
  {

  /**
   * A signed integer type that is exactly 8 bit wide
   *
   * @since 1.0.0
   */
#ifdef __DOXYGEN__
  using int8_t = implementation_defined;
#else
  using int8_t = __INT8_TYPE__;
#endif

  /**
   * A signed integer type that is exactly 16 bit wide
   *
   * @since 1.0.0
   */
#ifdef __DOXYGEN__
  using int16_t = implementation_defined;
#else
  using int16_t = __INT16_TYPE__;
#endif

  /**
   * A signed integer type that is exactly 32 bit wide
   *
   * @since 1.0.0
   */
#ifdef __DOXYGEN__
  using int32_t = implementation_defined;
#else
  using int32_t = __INT32_TYPE__;
#endif

  /**
   * A signed integer type that is exactly 64 bit wide
   *
   * @since 1.0.0
   */
#ifdef __DOXYGEN__
  using int64_t = implementation_defined;
#else
  using int64_t = __INT64_TYPE__;
#endif

  /**
   * An unsigned integer type that is exactly 8 bit wide
   *
   * @since 1.0.0
   */
#ifdef __DOXYGEN__
  using uint8_t = implementation_defined;
#else
  using uint8_t = __UINT8_TYPE__;
#endif

  /**
   * An unsigned integer type that is exactly 16 bit wide
   *
   * @since 1.0.0
   */
#ifdef __DOXYGEN__
  using uint16_t = implementation_defined;
#else
  using uint16_t = __UINT16_TYPE__;
#endif

  /**
   * An unsigned integer type that is exactly 32 bit wide
   *
   * @since 1.0.0
   */
#ifdef __DOXYGEN__
  using uint32_t = implementation_defined;
#else
  using uint32_t = __UINT32_TYPE__;
#endif

  /**
   * An unsigned integer type that is exactly 64 bit wide
   *
   * @since 1.0.0
   */
#ifdef __DOXYGEN__
  using uint64_t = implementation_defined;
#else
  using uint64_t = __UINT64_TYPE__;
#endif


  }

#endif

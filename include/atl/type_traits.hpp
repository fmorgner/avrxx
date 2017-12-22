#ifndef ATL_TYPE_TRAITS_HPP
#define ATL_TYPE_TRAITS_HPP

/**
 * @file
 * @brief An implemetation of the ISO14882:2017 type_traits header
 *
 * @since 1.0.0
 */

namespace atl
  {

  /**
   * @brief A wrapper for a static constant of an integral type
   *
   * @tparam ValueType An integral type
   * @tparam Value A value of the integral type specified by @p ValueType
   */
  template<typename ValueType, ValueType Value>
  struct integral_constant
    {
    /**
     * The type of the #integral_constant itself
     */
    using type = integral_constant;

    /**
     * The type of the wrapped value
     */
    using value_type = ValueType;

    /**
     * The wrapped static constant
     */
    static value_type constexpr value = Value;

    /**
     * Implicit conversion to a value of type #value_type
     */
    constexpr operator value_type() const noexcept { return value; }

    /**
     * Call the #integral_constant to retrieve its value
     */
    constexpr value_type operator()() const noexcept { return value; }
    };

  /**
   * @brief A convenience variable template that provides direct access to the value member of an #integral_constant
   *
   * @tparam ValueType An integral type
   * @tparam Value A value of the integral type specified by @p ValueType
   *
   * @see atl::integral_constant
   */
  template<typename ValueType, ValueType Value>
  auto constexpr integral_constant_v = integral_constant<ValueType, Value>::value;

  using false_type = integral_constant<bool, false>;

  using true_type = integral_constant<bool, true>;

  /**
   * @brief A template to test if a given type is an enum type
   *
   * An instance of this template provides all the members of an #integral_constant of type @p bool that are set accordingly.
   *
   * @tparam Candidate A type to test
   */
  template<typename Candidate>
  struct is_enum : integral_constant<bool, __is_enum(Candidate)> { };

  /**
   * @brief A template to test if a given type is a union type
   *
   * An instance of this template provides all the members of an #integral_constant of type @p bool that are set accordingly.
   *
   * @tparam Candidate A type to test
   */
  template<typename Candidate>
  struct is_union : integral_constant<bool, __is_union(Candidate)> { };

  /**
   * @brief A template to test if a given type is a class type
   *
   * An instance of this template provides all the members of an #integral_constant of type @p bool that are set accordingly.
   *
   * @tparam Candidate A type to test
   */
  template<typename Candidate>
  struct is_class : integral_constant<bool, __is_class(Candidate)> { };

  /**
   * @brief A template to determine the unsigned variant of a given signed type
   *
   * This template provides a member type @p type that is the unsigned equivalent of the given type.
   *
   * @tparam SignedType A signed integral type
   */
  template<typename SignedType>
  struct make_unsigned { using type = SignedType; };

  template<>
  struct make_unsigned<signed char> { using type = unsigned char; };

  template<>
  struct make_unsigned<signed short> { using type = unsigned short; };

  template<>
  struct make_unsigned<signed int> { using type = unsigned int; };

  template<>
  struct make_unsigned<signed long> { using type = unsigned long; };

  template<>
  struct make_unsigned<signed long long> { using type = unsigned long long; };

  }

#endif

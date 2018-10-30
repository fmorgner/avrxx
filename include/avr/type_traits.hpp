#ifndef AVR_TYPE_TRAITS_HPP
#define AVR_TYPE_TRAITS_HPP

/**
 * @file
 * @brief A partial implemetation of the ISO14882:2017 type_traits header
 *
 * This header provides a partial implementation of the @p type_traits header
 * as specified by the C++ language standard, with the addition of some
 * extensions.
 *
 * @since 1.0.0
 */

namespace avr
  {

  /**
   * @brief A helper for hiding template spezializations using SFINAE
   *
   * @tparam Condition A boolean-valued expression to check
   * @tparam EnabledType The type to provide if @c Condition is @c true
   *
   * @since 1.0.0
   */
  template<bool Condition, typename EnabledType = void>
  struct enable_if {};

  /**
   * @brief Specialization of avr::enable_if in case the condition holds
   *
   * @tparam EnabledType The type to provide if @c Condition is @c true
   *
   * @since 1.0.0
   */
  template<typename EnabledType>
  struct enable_if<true, EnabledType> { using type = EnabledType; };

  /**
   * @brief A convenience type alias for avr::enable_if
   *
   * @tparam Condition A boolean-valued expression to check
   * @tparam EnabledType The type to provide if @c Condition is @c true
   *
   * @since 1.0.0
   */
  template<bool Condition, typename EnabledType>
  using enable_if_t = typename enable_if<Condition, EnabledType>::type;

  /**
   * @brief A wrapper for a static constant of an integral type
   *
   * @tparam ValueType An integral type
   * @tparam Value A value of the integral type specified by @p ValueType
   *
   * @since 1.0.0
   */
  template<typename ValueType, ValueType Value>
  struct integral_constant
    {
    /**
     * The type of the avr::integral_constant itself
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
     * Implicit conversion to a value of type avr::value_type
     */
    constexpr operator value_type() const noexcept { return value; }

    /**
     * Call the avr::integral_constant to retrieve its value
     */
    constexpr value_type operator()() const noexcept { return value; }
    };

  /**
   * @brief A convenience variable template that provides direct access to the value member of an avr::integral_constant
   *
   * @tparam ValueType An integral type
   * @tparam Value A value of the integral type specified by @p ValueType
   *
   * @see avr::integral_constant
   *
   * @since 1.0.0
   */
  template<typename ValueType, ValueType Value>
  auto constexpr integral_constant_v = integral_constant<ValueType, Value>::value;

  /**
   * @brief A convenience type to represent a static boolean constant with a value of <code>false</code>
   */
  using false_type = integral_constant<bool, false>;

  /**
   * @brief A convenience type to represent a static boolean constant with a value of <code>true</code>
   */
  using true_type = integral_constant<bool, true>;

  /**
   * @brief A template to test if a given type is an enum type
   *
   * An instance of this template provides all the members of an avr::integral_constant of type @p bool that are set accordingly.
   *
   * @tparam Candidate A type to test
   *
   * @since 1.0.0
   */
  template<typename Candidate>
  struct is_enum : integral_constant<bool, __is_enum(Candidate)> { };

  /**
   * @brief A template to test if a given type is a union type
   *
   * An instance of this template provides all the members of an avr::integral_constant of type @p bool that are set accordingly.
   *
   * @tparam Candidate A type to test
   *
   * @since 1.0.0
   */
  template<typename Candidate>
  struct is_union : integral_constant<bool, __is_union(Candidate)> { };

  /**
   * @brief A template to test if a given type is a class type
   *
   * An instance of this template provides all the members of an avr::integral_constant of type @p bool that are set accordingly.
   *
   * @tparam Candidate A type to test
   *
   * @since 1.0.0
   */
  template<typename Candidate>
  struct is_class : integral_constant<bool, __is_class(Candidate)> { };

  /**
   * @brief Remove top-level qualification from a type
   *
   * @tparam Type The type to remove the const from
   *
   * @since 1.0.0
   */
  template<typename Type>
  struct remove_const { using type = Type; };

  /**
   * @brief Specialization of avr::remove_const for types that are const qualified
   *
   * @tparam Type The type to remove the const from
   *
   * @since 1.0.0
   */
  template<typename Type>
  struct remove_const<Type const> { using type = Type; };

  /**
   * @brief A convenience type alias for avr::remove_const
   *
   * @tparam Type The type to remove the const from
   *
   * @since 1.0.0
   */
  template<typename Type>
  using remove_const_t = typename remove_const<Type>::type;

  /**
   * @brief A template to determine the unsigned variant of a given signed type
   *
   * This template provides a member type @p type that is the unsigned equivalent of the given type.
   *
   * @tparam SignedType A signed integral type
   *
   * @since 1.0.0
   */
  template<typename SignedType>
  struct make_unsigned { using type = SignedType; };

  /**
   * @brief Specialization of avr::make_unsigned for <code>signed char</code>
   *
   * @since 1.0.0
   */
  template<>
  struct make_unsigned<signed char> { using type = unsigned char; };

  /**
   * @brief Specialization of avr::make_unsigned for <code>signed short</code>
   *
   * @since 1.0.0
   */
  template<>
  struct make_unsigned<signed short> { using type = unsigned short; };

  /**
   * @brief Specialization of avr::make_unsigned for <code>signed int</code>
   *
   * @since 1.0.0
   */
  template<>
  struct make_unsigned<signed int> { using type = unsigned int; };

  /**
   * @brief Specialization of avr::make_unsigned for <code>signed long</code>
   *
   * @since 1.0.0
   */
  template<>
  struct make_unsigned<signed long> { using type = unsigned long; };

  /**
   * @brief Specialization of avr::make_unsigned for <code>signed long long</code>
   *
   * @since 1.0.0
   */
  template<>
  struct make_unsigned<signed long long> { using type = unsigned long long; };

  /**
   * @brief A type to select between two types bassed on the given predicate
   *
   * @since 1.0.0
   */
  template<bool Predicate, typename, typename ElseType>
  struct conditional { using type = ElseType; };

  template<typename ThenType, typename ElseType>
  struct conditional<true, ThenType, ElseType> { using type = ThenType; };

  template<bool Predicate, typename ThenType, typename ElseType>
  using conditional_t = typename conditional<Predicate, ThenType, ElseType>::type;

  }

#endif

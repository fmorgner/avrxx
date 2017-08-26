#ifndef ATL_META_HPP
#define ATL_META_HPP

/**
 * @brief The <i>Template Meta-Programming Library</i>
 */
namespace atl::meta
  {

  /**
   * @brief A helper for hiding template spezializations using SFINAE
   *
   * @tparam Condition A boolean-valued expression to check
   * @tparam EnabledType The type to provide if @c Condition is @c true
   */
  template<bool Condition, typename EnabledType = void>
  struct enable_if {};

  template<typename EnabledType>
  struct enable_if<true, EnabledType> { using type = EnabledType; };

  /**
   * @brief A convenience type alias for #enable_if
   *
   * @tparam Condition A boolean-valued expression to check
   * @tparam EnabledType The type to provide if @c Condition is @c true
   */
  template<bool Condition, typename EnabledType>
  using enable_if_t = typename enable_if<Condition, EnabledType>::type;

  /**
   * @brief Remove top-level qualification from a type
   *
   * @tparam Type The type to remove the const from
   */
  template<typename Type>
  struct remove_const { using type = Type; };

  template<typename Type>
  struct remove_const<Type const> { using type = Type; };

  /**
   * @brief A convenience type alias for #remove_const
   *
   * @tparam Type The type to remove the const from
   */
  template<typename Type>
  using remove_const_t = typename remove_const<Type>::type;

  /**
   * @brief Check if a given value is in a speific range
   *
   * @param value The value to check
   * @param low The lower bound (inclusive)
   * @param hight The upper bound (inclusive)
   */
  template<typename ValueType>
  constexpr auto in_range(ValueType value, ValueType low, ValueType high) { return value >= low && value <= high; }

  }

#endif

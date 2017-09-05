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
   * @brief Wrap a constant of integral type
   *
   * @tparam Type The type of the value
   * @tparam Value The wrapped value
   */
  template<typename Type, Type Value>
  struct integral_constant
    {
    /**
     * @brief The type of the wrapped value
     */
    using value_type = Type;

    /**
     * @brief The wrapped value
     */
    static value_type constexpr value{Value};

    /**
     * @brief Access the wrapped value
     */
    constexpr value_type operator()() const { return value; }

    /**
     * @brief Convert the instance into the wrapped value
     */
    constexpr operator value_type() const { return (*this)(); }
    };

  /**
   * @brief Convenience variable template for accessing #integral_constant values
   */
  template<typename Type, Type Value>
  auto constexpr integral_constant_v = integral_constant<Type, Value>::value;

  /**
   * @brief Convenience alias for an #integral_constant containing false
   */
  using false_type = integral_constant<bool, false>;

  /**
   * @brief Convenience alias for an #integral_constant containing true
   */
  using true_type = integral_constant<bool, true>;

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
   * @brief Check if two types are the same
   *
   * Two types are considered the same, if they name the same type with identical cv-qualification
   */
  template<typename LhsType, typename RhsType>
  struct is_same : false_type { };

  template<typename Type>
  struct is_same<Type, Type> : true_type { };

  /**
   * @brief Convenience variable template to check if two types are the same
   *
   * @see #is_same
   */
  template<typename LhsType, typename RhsType>
  auto constexpr is_same_v = is_same<LhsType, RhsType>::value;

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

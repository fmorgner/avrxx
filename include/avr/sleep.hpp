#ifndef AVR_SLEEP_HPP
#define AVR_SLEEP_HPP

#include <avr/sleep.h>

/**
 * @brief The AVR power saving sleep API wrapper
 */
namespace avr::sleep
  {

  /**
   * @brief AVR microcontroller sleep modes
   *
   * AVR microcontrollers support multiple different sleep modes, designed to save power by disabling certain modules of the
   * controller. Not all controllers support all of the five available sleep modes:
   *
   * @arg @link avr::sleep::mode::idle Idle Sleep @endlink
   * @arg @link avr::sleep::mode::power_down Power Down @endlink
   * @arg @link avr::sleep::mode::power_save Power Save @endlink
   * @arg @link avr::sleep::mode::standby Standby @endlink
   * @arg @link avr::sleep::mode::extended_standby Extended Standby @endlink
   *
   * There is one additional mode, called @link avr::sleep::mode::adc_noise_reduction ADC Noise Reduction @endlink that is
   * designed to reduce the Anonlog-Digital-Converter (ADC) noise for higher precision sampling.
   */
  enum struct mode : uint8_t
    {
    /**
     * @brief Idle sleep
     *
     * The <b>Idle</b> sleep mode disables the CPU and Flash clocks of the controller. Other peripherals, like the:
     *
     * @arg Serial Peripheral Interface (SPI)
     * @arg Universal Synchronous/Asynchronous Receiver/Transmitter (USART)
     * @arg Analog Comparator
     * @arg 2-wire Serial Interface (TWI)
     * @arg Timers/Counters
     * @arg Watchdog Timer
     * @arg Interrupt system
     *
     * are still available during this sleep mode. This sleep mode makes it possible to wake the controller up via internal
     * and external interrupts.
     */
#ifdef SLEEP_MODE_IDLE
    idle = SLEEP_MODE_IDLE,
#else
    idle,
#endif


    /**
     * @brief ADC Noise Reduction sleep
     *
     * <b>ADC Noise Reduction</b> sleep is used to reduce the amount of noise the Analog Digital Converter picks up during
     * conversion. This sleep mode differs from @link avr::sleep::mode::idle Idle @endlink in that it also disables * the I/O
     * clock of the controller.
     */
#ifdef SLEEP_MODE_ADC
    adc_noise_reduction = SLEEP_MODE_ADC,
#else
    adc_noise_reduction,
#endif

    /**
     * @brief Power Down sleep
     *
     * In addition to the power saving features of @link avr::sleep::mode::idle Idle @endlink, <b>Power Down</b> sleep mode
     * disables the external oscillator. External interrupts, as well as the 2-wire Serial Interface (TWI) address watch
     * interrupt and the Watchdog are still available. The controller can only be woken up by the following events:
     *
     * @arg External Reset
     * @arg Watchdog System Reset
     * @arg Watchdog Interrupt
     * @arg Brown-out Detection Reset
     * @arg 2-Wire Serial Interface (TWI) address match interrupt
     * @arg External level interrupt on the INT interface
     * @arg Level Change interrupts
     */
#ifdef SLEEP_MODE_PWR_DOWN
    power_down = SLEEP_MODE_PWR_DOWN,
#else
    power_down,
#endif

    /**
     * @brief Power Save sleep
     *
     * This power save mode is almost identical to the @link avr::sleep::mode::power_down Power Down @endlink. Contrary to
     * the Power Down sleep, Timer/Counter2 is still available. If Timer/Counter2 is not required, Power Down sleep mode
     * should be preferred.
     */
#ifdef SLEEP_MODE_PWR_SAVE
    power_save = SLEEP_MODE_PWR_SAVE,
#else
    power_save,
#endif

    /**
     * @brief Standby sleep
     *
     * <b>Standby</b> sleep only differs from @link avr::sleep::mode::power_down Power Down @endlink sleep in that the external
     * oscillator is not disabled.
     */
#ifdef SLEEP_MODE_STANDBY
    standby = SLEEP_MODE_STANDBY,
#else
    standby,
#endif

    /**
     * @brief Extended Standby sleep
     *
     * <b>Extended Standby</b> sleep only differs from @link avr::sleep::mode::power_save Power Save @endlink sleep in that
     * the external oscillator is not disabled.
     */
#ifdef SLEEP_MODE_EXT_STANDBY
    extended_standby = SLEEP_MODE_EXT_STANDBY,
#else
    extended_standby,
#endif
    };

  /**
   * @brief Select the sleep #mode the controller will use
   *
   * The sleep mode the controller will enter must be selected before calling #enter() . AVR microcontrollers * support
   * different sleep modes as described by the #avr::sleep::mode enumeration.
   *
   * @tparam Mode The desired sleep mode
   *
   * @see #enter(), #enable(), #sleep()
   */
  template<mode Mode>
  void select()
    {
    if constexpr(Mode == mode::idle)
      {
#ifndef SLEEP_MODE_IDLE
#error "Idle sleep is not supported by the device"
#endif
      }
    else if constexpr(Mode == mode::adc_noise_reduction)
      {
#ifndef SLEEP_MODE_ADC
#error "ADC Noise Reduction sleep is not supported by the device"
#endif
      }
    if constexpr(Mode == mode::power_down)
      {
#ifndef SLEEP_MODE_PWR_DOWN
#error "Power Down sleep is not supported by the device"
#endif
      }
    else if constexpr(Mode == mode::power_save)
      {
#ifndef SLEEP_MODE_PWR_SAVE
#error "Power Save sleep is not supported by the device"
#endif
      }
    else if constexpr(Mode == mode::standby)
      {
#ifndef SLEEP_MODE_STANDBY
#error "Standby sleep is not supported by the device"
#endif
      }
    else if constexpr(Mode == mode::extended_standby)
      {
#ifndef SLEEP_MODE_EXT_STANDBY
#error "Extended Standby sleep is not supported by the device"
#endif
      }

    set_sleep_mode(static_cast<int>(Mode)); return;
    }

  /**
   * @brief Disable the <b>Brown-out Detector</b>
   *
   * On supported devices, disabling the Brown-out Detector (BOD) can significantly reduce the power consumption during sleep.
   * This difference is especialy noticeable in deeper sleep modes.
   *
   * @note Due to the hardware implementation of the mechanism for disabling the BOD, there is only a small window of time
   * prior to entering sleep in which the BOD will be fully disabled. Atmel recommends that this function is followed
   * directly by enabling the interrupts and putting the controller to sleep.
   *
   * @see sleep(), #enable(), #select()
   */
  inline void disable_brownout_detector()
    {
#ifdef sleep_bod_disable
    sleep_bod_disable();
#else
#error "Disabling Brown-out Detection is not supported by the device"
#endif
    }

  /**
   * @brief Prepare the controller for sleeping and enter the previously selected sleep #mode
   *
   * After selecting the desired sleep mode using #select(), this function can be used to enter the sleep mode. Calling this
   * function is equivalent to calling #enable() followed by #sleep().
   *
   * @note If no interrupts have been enabled prior to calling this function, the controller will effectively be halted until
   * a system reset occurs.
   *
   * @see #select(), #select_enter()
   */
  inline void enter() { sleep_mode(); }

  /**
   * @brief Select and enter the desired sleep #mode
   *
   * This function selects the desired sleep mode (as if by calling #select()) and immediately enters sleep (as if by calling
   * #enter()). The same caveat regarding interrupts applies as for #enter().
   *
   * @tparam Mode The desired sleep mode
   *
   * @see #select(), #enter()
   */
  template<mode Mode> void select_enter() { select<Mode>(); enter(); }

  /**
   * @brief Prepare the controller for sleeping
   *
   * After selecting the desired sleep #mode, the controller must be prepared for sleeping by calling this function prior to
   * calling #sleep(). This sets the <i>Sleep Enable</i> bit, so that when the <b>SLEEP</b> instruction is issued, the
   * controller enters the sleep mode.
   *
   * @see #enter()
   */
  inline void enable() { sleep_enable(); }

  /**
   * @brief Select the desired sleep #mode and prepare the controller for sleeping
   *
   * This function selects the desired sleep mode (as if by calling #select()) and prepares the controller for sleep (as if by
   * calling #enable()).
   *
   * @tparam Mode The desired sleep mode
   *
   * @see #select(), #enable()
   */
  template<mode Mode> void select_enable() { select<Mode>(); enable(); }

  /**
   * @brief Prevent the controller for sleeping
   *
   * Calling this function disables the sleep function for the microcontroller. It can be used to prevent entering sleep and
   * is automatically called after the controller wakes up from #sleep().
   *
   * @see #enable()
   */
  inline void disable() { sleep_disable(); }

  /**
   * @brief Enter the previously selected and prepared sleep #mode
   *
   * After selecting a sleep and preparing the controller for going to sleep, this function initiates the sleep. When the
   * controller is woken up, e.g. by an external interrupt, the sleep mode will be disabled, the interrupt will be handles,
   * and execution continues from the point at which #sleep() was called.
   *
   * @see #select(), #enable()
   */
  inline void sleep() { sleep_cpu(); disable(); }

  }

#endif

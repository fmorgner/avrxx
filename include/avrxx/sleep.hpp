#ifndef AVRXX_SLEEP_HPP
#define AVRXX_SLEEP_HPP

#include <avr/sleep.h>

namespace avr
  {

  enum struct mode : uint8_t
    {
#ifdef SLEEP_MODE_IDLE
    idle = SLEEP_MODE_IDLE,
#else
    idle,
#endif


#ifdef SLEEP_MODE_ADC
    adc_noise_reduction = SLEEP_MODE_ADC,
#else
    adc_noise_reduction,
#endif

#ifdef SLEEP_MODE_PWR_DOWN
    power_down = SLEEP_MODE_PWR_DOWN,
#else
    power_down,
#endif

#ifdef SLEEP_MODE_PWR_SAVE
    power_save = SLEEP_MODE_PWR_SAVE,
#else
    power_save,
#endif

#ifdef SLEEP_MODE_STANDBY
    standby = SLEEP_MODE_STANDBY,
#else
    standby,
#endif

#ifdef SLEEP_MODE_EXT_STANDBY
    extended_standby = SLEEP_MODE_EXT_STANDBY,
#else
    extended_standby,
#endif
    };

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

  inline void disable_brownout_detector()
    {
#ifdef sleep_bod_disable
    sleep_bod_disable();
#else
#error "Disabling Brown-out Detection is not supported by the device"
#endif
    }

  inline void enter() { sleep_mode(); }

  template<mode Mode> void select_enter() { select<Mode>(); enter(); }

  inline void enable() { sleep_enable(); }

  template<mode Mode> void select_enable() { select<Mode>(); enable(); }

  inline void disable() { sleep_disable(); }

  inline void sleep() { sleep_cpu(); disable(); }

  }

#endif

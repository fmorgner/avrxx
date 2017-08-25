#ifndef AVR_SLEEP_HPP
#define AVR_SLEEP_HPP

#include <avr/sleep.h>

namespace avr
  {

  namespace sleep
    {

    enum struct mode : uint8_t
      {
      idle,
      adc_noise_reduction,
      power_down,
      power_save,
      standby,
      extended_standby,

      };

    template<mode Mode>
    void select()
      {
      if constexpr(Mode == mode::idle)
        {
#ifdef SLEEP_MODE_IDLE
        set_sleep_mode(SLEEP_MODE_IDLE); return;
#else
#error "Idle sleep is not supported by the device"
#endif
        }
      else if constexpr(Mode == mode::adc_noise_reduction)
        {
#ifdef SLEEP_MODE_ADC
        set_sleep_mode(SLEEP_MODE_ADC); return;
#else
#error "ADC Noise Reduction sleep is not supported by the device"
#endif
        }
      if constexpr(Mode == mode::power_down)
        {
#ifdef SLEEP_MODE_PWR_DOWN
        set_sleep_mode(SLEEP_MODE_PWR_DOWN); return;
#else
#error "Power Down sleep is not supported by the device"
#endif
        }
      else if constexpr(Mode == mode::power_save)
        {
#ifdef SLEEP_MODE_PWR_SAVE
        set_sleep_mode(SLEEP_MODE_PWR_SAVE); return;
#else
#error "Power Save sleep is not supported by the device"
#endif
        }
      else if constexpr(Mode == mode::standby)
        {
#ifdef SLEEP_MODE_STANDBY
        set_sleep_mode(SLEEP_MODE_STANDBY); return;
#else
#error "Standby sleep is not supported by the device"
#endif
        }
      else if constexpr(Mode == mode::extended_standby)
        {
#ifdef SLEEP_MODE_EXT_STANDBY
        set_sleep_mode(SLEEP_MODE_EXT_STANDBY); return;
#else
#error "Extended Standby sleep is not supported by the device"
#endif
        }
      }

    inline void enter() { sleep_mode(); }

    template<mode Mode> void enter() { select<Mode>(); enter(); }

    inline void enable() { sleep_enable(); }

    template<mode Mode> void enable() { select<Mode>(); enable(); }

    inline void sleep() { sleep_cpu(); sleep_disable(); }

    inline void disable_brownout_detection()
      {
#ifdef sleep_bod_disable
      sleep_bod_disable();
#else
#error "Disabling Brown-out Detection is not supported by the device"
#endif
      }

    }

  }

#endif

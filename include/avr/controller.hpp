#ifndef AVR_CONTROLLER_HPP
#define AVR_CONTROLLER_HPP

/**
 * @file
 * @brief This file provides a type alias <code>atl::mcu</code> that maps to the correct underlying implementation
 *
 * @since 1.0.0
 */

#ifndef __AVR_DEVICE_NAME__
#error "No AVR device specified. Please supply the appropriate -mmcu=<your_device> compiler flag"
#endif

#if defined(__AVR_ATmega328P__)
#include "avr/controller/mega328p.h"
#elif defined(__DOXYGEN__)
namespace avr
  {
  /**
   * @brief The selected MCU type
   *
   * @since 1.0.0
   */
  using mcu = internal_mcu_type;
  }
#else
#error "Unsupported AVR device"
#endif

#endif

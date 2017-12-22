#ifndef AVR_CONTROLLER_HPP
#define AVR_CONTROLLER_HPP

/**
 * @file
 * @brief This file provides a type alias
 */

#ifndef __AVR_DEVICE_NAME__
#error "No AVR device specified. Please supply the appropriate -mmcu=<your_device> compiler flag"
#endif

#if defined(__AVR_ATmega328P__)
#include "avr/internal/controllers/mega328p.h"
#elif defined(DOXYGEN)
namespace avr { using mcu = internal_mcu_type; }
#else
#error "Unsupported AVR device"
#endif

#endif

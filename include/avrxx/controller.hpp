#ifndef AVRXX_CONTROLLER_HPP
#define AVRXX_CONTROLLER_HPP

#ifndef __AVR_DEVICE_NAME__
#error "No AVR device specified. Please supply the appropriate -mmcu=<your_device> compiler flag"
#endif

#if defined(__AVR_ATmega328P__)
#include "avrxx/controller/mega328p.hpp"
#else
#error "Unsupported AVR device"
#endif

#endif

#include <avr/controller.hpp>

int main()
  {
  if(avr::mcu::pinc::get_pin<3>())
    {
    return avr::mcu::pinc::get_pin_unsafe(4);
    }
  return avr::mcu::pinc::get_pin<6>();
  }

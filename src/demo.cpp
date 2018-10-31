#include <avr/controller.hpp>

int main()
  {
  if(avr::mcu::pinc::get_bit<3>())
    {
    return avr::mcu::pinc::get_bit<4>();
    }
  return avr::mcu::pinc::get_bit<6>();
  }

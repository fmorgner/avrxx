#include <avr/controller.hpp>

int main()
  {
  if(avr::mcu::portb::port<3>::get())
    {
    avr::mcu::portb::port<7>::set();
    }
  else
    {
    avr::mcu::portb::port<7>::get();
    }
  }

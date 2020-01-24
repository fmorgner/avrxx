#include <avrxx/controller.hpp>

int main()
  {
  if(avr::mcu::pinc::get_pin<3>())
    {
    avr::mcu::portc::set_bit_unsafe(4);
    }
  }

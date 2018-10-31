#include <avr/controller.hpp>

int main()
  {
  avr::mcu::ddrc::set_bit<5>();
  avr::mcu::portc::set_bit<5>();
  }

#include <avr/controller.hpp>
#include <avr/flash_constant.hpp>

//static auto const blub = avr::flash_constant{0xfeca12};

int main()
  {
  if(avr::mcu::pinc::get_bit<3>())
    {
    return avr::mcu::pinc::get_bit<4>();
    }
  return avr::mcu::pinc::get_bit<6>();
//  return blub;
  }

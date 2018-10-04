#include <avr/controller.hpp>
#include <avr/cstdint.hpp>
#include <avr/flash_constant.hpp>
#include <avr/string_util.hpp>

static auto const blub = avr::flash_constant{0xfeca12};

int main()
  {
  avr::mcu::pinc::pin<3>::get();
  return blub;
  }

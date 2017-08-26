#include "avr/internal/registers.hpp"

struct some_device
  {
  struct gpio_ports
    {
    static auto constexpr B = avr::internal::registers::io_register_8<0x03>;
    };
  };

int main()
  {
  auto constexpr & portB = some_device::gpio_ports::B;

  if(portB.bit<3>.get())
    {
    portB.bit<7>.set();
    }
  else
    {
    portB.bit<7>.clear();
    }
  }

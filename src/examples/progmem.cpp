#include <avrxx/flash_constant.hpp>

#include <cstdint>

auto const demo = avr::flash_constant{1};

int main()
  {
  return demo;
  }

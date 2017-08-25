#include "avr/sleep.hpp"

int main()
  {
  avr::sleep::enter<avr::sleep::mode::idle>();
  }

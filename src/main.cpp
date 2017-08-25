#include "avr/sleep.hpp"

int main()
  {
  avr::sleep::select_enter<avr::sleep::mode::idle>();
  }

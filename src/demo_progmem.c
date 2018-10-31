#include <avr/pgmspace.h>
#include <stdint.h>

int const demo PROGMEM = 1;

int main()
  {
  return pgm_read_word(&demo);
  }

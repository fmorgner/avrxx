#include <avr/io.h>

int main()
  {
  if(PINC & (1 << PC3))
    {
    return !!(PINC & (1 << 4));
    }
  return !!(PINC & (1 << 6));
  }

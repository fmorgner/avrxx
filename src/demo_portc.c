#include <avr/io.h>

int main() {
  DDRC |= (1 << DDC5);
  PORTC |= (1 << DDC5);
}

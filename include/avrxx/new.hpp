#ifndef AVR_NEW_HPP
#define AVR_NEW_HPP

#include "avr/cstddef.hpp"
#include <stdlib.h>

void * operator new(avr::size_t size)
  {
  return malloc(size);
  }

void * operator new(avr::size_t, void * destination)
  {
  return destination;
  }

void operator delete(void * ptr) noexcept
  {
  free(ptr);
  }

void operator delete(void *, void *) noexcept
  {
  }

#endif

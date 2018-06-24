#include <avr/controller.hpp>
#include <avr/readonly.hpp>

#include <atl/string_util.hpp>

struct foo
  {
  // avr::readonly<int> const v1;
  // avr::readonly<int> const v2;
  int const v1;
  int const v2;
  };

static avr::readonly<foo> blub{{0x1234, 0x5678}};

using mcu = avr::internal::controllers::mega328p;

int main()
  {
  return blub.get().v1 + blub.get().v2;
  // blub.v2.get();

  mcu::pinc::pin<3>::get();
  }

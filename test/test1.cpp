#include <iostream>

#include "base.hpp"

int main() {
  auto str = "helloworld";  // 2So3BOfkHolCB2
  auto str62 = kotucode::base::base62::encode(str);
  std::cout << str << std::endl;
  std::cout << str62 << std::endl;
  std::cout << kotucode::base::base62::decode(str62) << std::endl;
}

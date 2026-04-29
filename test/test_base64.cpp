#include <cassert>
#include <cstdlib>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "base.hpp"

static std::vector<std::pair<std::string, std::string>> test_cases{{"helloworld", ""}};

#if 0

int main() {
  for (auto&& test_case : test_cases) {
    using kotucode::base::base64::decode;
    using kotucode::base::base64::encode;
    auto encoded = encode(test_case.first);
    auto decoded = decode(test_case.second);
#ifndef NDEBUG
    std::cout << "Debug Mode" << std::endl;
    assert(encoded == test_case.second);
    assert(test_case.first == decoded);
#else
    std::cout << "Release Mode" << std::endl;
    if (encoded != test_case.second) return EXIT_FAILURE;
    if (test_case.first != decoded) return EXIT_FAILURE;
#endif
  }
  return EXIT_SUCCESS;
}

#else

int main() {
  for (auto&& test_case : test_cases) {
    using kotucode::base::base64::decode;
    using kotucode::base::base64::encode;
    std::cout << "[" << test_case.first;
    std::cout << "] -> [";
    std::cout << encode(test_case.first) << "]";
    std::cout << std::endl;
  }
  return EXIT_SUCCESS;
}

#endif

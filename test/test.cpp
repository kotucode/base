#include <cassert>
#include <cstdlib>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "base.hpp"

static std::vector<std::pair<std::string, std::string>> test_cases{
    {"helloworld", "aGVsbG93b3JsZA=="},
    {"Hello مرحبا 世界", "SGVsbG8g2YXYsdit2KjYpyDkuJbnlYw="},
    {"ça va?", "Y8ynYSB2YT8="},
    {"สวัสดี", "4Liq4Lin4Lix4Liq4LiU4Li1"},
};

int main() {
  for (auto&& test_case : test_cases) {
    using base64url = kotucode::base::alphabet::base64url;
    using kotucode::base::base64::decode;
    using kotucode::base::base64::encode;
    using kotucode::base::base64::pad;
    using kotucode::base::base64::trim;
    std::cout << "[" << test_case.first;
    std::cout << "] -> [";
    std::cout << encode<base64url>(test_case.first) << "]";
    std::cout << " -> [" << decode<base64url>(encode<base64url>(test_case.first)) << "]";
    // std::cout << " -> [" << trim<base64url>(encode<base64url>(test_case.first)) << "]";
    // std::cout << " -> [" << pad<base64url>(encode<base64url>(test_case.first)) << "]";
    std::cout << std::endl;
  }
  return EXIT_SUCCESS;
}

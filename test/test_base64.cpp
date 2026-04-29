#include <cassert>
#include <cstdlib>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "base.hpp"

static std::vector<std::pair<std::string, std::string>> test_cases{
    {"helloworld", "aGVsbG93b3JsZA=="},
    {"Hello 你好 こんにちは 안녕하세요 Γεια σας Hello 世界",
     "SGVsbG8g5L2g5aW9IOOBk+OCk+OBq+OBoeOBryDslYjrhZXtlZjshLjs"
     "mpQgzpPOtc65zrEgz4POsc+CIEhlbGxvIOS4lueVjA=="},
    {"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz",
     "QUJDREVGR0hJSktMTU5PUFFSU1RVVldYWV"
     "phYmNkZWZnaGlqa2xtbm9wcXJzdHV2d3h5eg=="},
    {"ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖØÙÚÛÜÝÞß",
     "w4DDgcOCw4PDhMOFw4bDh8OIw4nDisOLw4zDjcO"
     "Ow4/DkMORw5LDk8OUw5XDlsOYw5nDmsObw5zDncOew58="},
    {"АБВГДЕЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯабвгдежзийклмнопрстуфхцчшщъыьэюя",
     "0JDQkdCS0JPQlNCV0JbQl9CY0JnQmtCb0JzQndCe0J/QoNCh"
     "0KLQo9Ck0KXQptCn0KjQqdCq0KvQrNCt0K7Qr9Cw0LHQstCz0LT"
     "QtdC20LfQuNC50LrQu9C80L3QvtC/0YDRgdGC0YPRhNG"
     "F0YbRh9GI0YnRitGL0YzRjdGO0Y8="},
    {"ΑΒΓΔΕΖΗΘΙΚΛΜΝΞΟΠΡΣΤΥΦΧΨΩαβγδεζηθικλμνξοπρστυφχψω",
     "zpHOks6TzpTOlc6WzpfOmM6ZzprOm86czp3Ons6fzqDOoc6jzqTOpc6mzqfOqM6pzrHOss6zz"
     "rTOtc62zrfOuM65zrrOu868zr3Ovs6/z4DPgc+Dz4TPhc+Gz4fPiM+J"},
    {"ｱｲｳｴｵｶｷｸｹｺｻｼｽｾｿﾀﾁﾂﾃﾄﾅﾆﾇﾈﾉﾊﾋﾌﾍﾎﾏﾐﾑﾒﾓﾔﾕﾖﾗﾘﾛﾜﾝ",
     "772x772y772z7720772177227723772477257726772777287729772+772/"
     "776A776B776C776D776E776F776G776H776I776J776K776L776M776N776O776P776Q776R7"
     "76S776T776U776V776W776X776Y776b776c776d"},
    {"あいうえおかるれろわをん",
     "44GC44GE44GG44GI44GK44GL44KL44KM44KN44KP44KS44KT"},
    {"가나다라마바사아자차카타파하",
     "6rCA64KY64uk652866eI67CU7IKs7JWE7J6Q7LCo7Lm07YOA7YyM7ZWY"},
    {"☺♪♫☼♀♂⚡★☆", "4pi64pmq4pmr4pi84pmA4pmC4pqh4piF4piG"},
    {"😀🎵🌍🔍📱💻", "8J+YgPCfjrXwn4yN8J+UjfCfk7Hwn5K7"},
    {"ｱｲｳｴｵｶｷｸｹｺｻｼｽｾｿﾀﾁﾂﾃﾄﾅﾆﾇﾈﾉﾊﾋﾌﾍﾎﾏﾐﾑﾒﾓﾔﾕﾖﾗﾘﾛﾜﾝ",
     "772x772y772z7720772177227723772477257726772777287729772+772/"
     "776A776B776C776D776E776F776G776H776I776J776K776L776M776N776O776P776Q776R7"
     "76S776T776U776V776W776X776Y776b776c776d"},
    {"Hello مرحبا 世界", "SGVsbG8g2YXYsdit2KjYpyDkuJbnlYw="},
    {"ça va?", "Y8ynYSB2YT8="},
    {"สวัสดี", "4Liq4Lin4Lix4Liq4LiU4Li1"},
    {"שלום", "16nXnNeV150="},
};

#if 1

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

// Distributed under the MIT License that can be found in the LICENSE file.
// https://github.com/kotucode/base
//
// Author: Keunlas <keunlaz at gmail dot com>

#ifndef KEUNLAS_KOTUCODE_BASE_H_
#define KEUNLAS_KOTUCODE_BASE_H_

#include <algorithm>
#include <array>
#include <cstdint>
#include <string>
#include <vector>

namespace kotucode {
namespace base {

namespace alphabet {

/**
 * @brief Base62 编码字符集，提供 0-9、A-Z、a-z 共 62 个字符的正向与反向映射表。
 */
struct base62 {
  static const std::array<char, 62>& data() noexcept {
    static constexpr std::array<char, 62> data{
        {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C',
         'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
         'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c',
         'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
         'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'}};
    return data;
  }
  static const std::array<int8_t, 256>& rdata() noexcept {
    static constexpr std::array<int8_t, 256> rdata{
        {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
         -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
         -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 0,  1,  2,  3,  4,  5,
         6,  7,  8,  9,  -1, -1, -1, -1, -1, -1, -1, 10, 11, 12, 13, 14, 15, 16,
         17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34,
         35, -1, -1, -1, -1, -1, -1, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46,
         47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, -1, -1, -1,
         -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
         -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
         -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
         -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
         -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
         -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
         -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
         -1, -1, -1, -1}};
    return rdata;
  }
};

}  // namespace alphabet

namespace base62 {
namespace details {

/**
 *
 */
inline std::string encode(const std::string& binary_data,
                          const std::array<char, 62>& alphabet) {
  if (binary_data.empty()) return "";

  // 1. 统计输入中的前导零字节（0x00）个数
  std::size_t zeros = 0;
  while (zeros < binary_data.size() && binary_data[zeros] == 0) {
    ++zeros;
  }

  // 2. 将剩余字节复制到大整数向量（big-endian 表示，索引 0 为最高字节）
  std::vector<uint8_t> bignum;
  bignum.reserve(binary_data.size() - zeros);
  for (std::size_t i = zeros; i < binary_data.size(); ++i) {
    bignum.push_back(static_cast<uint8_t>(binary_data[i]));
  }

  // 3. 全零输入直接返回对应数量的 alphabet[0] 字符
  if (bignum.empty()) {
    return std::string(zeros, alphabet[0]);
  }

  std::string tmp;  // 临时存放逆序的编码字符（低位在前）
  tmp.reserve(binary_data.size() * 2);

  // 4. 反复执行“大整数 / base”操作，直到商为 0
  while (!bignum.empty()) {
    int carry = 0;
    // 从高位到低位处理每个字节
    for (std::size_t i = 0; i < bignum.size(); ++i) {
      int value = carry * 256 + bignum[i];
      bignum[i] = static_cast<uint8_t>(value / 62);
      carry = value % 62;
    }
    // 移除商的前导零，保持规范化
    std::size_t first_nonzero = 0;
    while (first_nonzero < bignum.size() && bignum[first_nonzero] == 0) {
      ++first_nonzero;
    }
    if (first_nonzero == bignum.size()) {
      bignum.clear();
    } else if (first_nonzero > 0) {
      bignum.erase(bignum.begin(), bignum.begin() + first_nonzero);
    }
    // carry 即为本次除法的余数，对应一个 base 字符
    tmp.push_back(alphabet[carry]);
  }

  // 5. 组合最终结果：前导“0”字符 + 反转后的 tmp
  std::string result;
  result.reserve(zeros + tmp.size());
  result.append(zeros, alphabet[0]);
  std::reverse(tmp.begin(), tmp.end());
  result.append(tmp);

  return result;
}

/**
 *
 */
inline std::string decode(const std::string& base_string,
                          const std::array<int8_t, 256>& rdata) {
  if (base_string.empty()) return "";

  // 1. 找到 alphabet[0] 对应的字符（用于前导零处理）
  char zero_char = 0;
  bool found_zero = false;
  for (int i = 0; i < 256; ++i) {
    if (rdata[i] == 0) {
      zero_char = static_cast<char>(i);
      found_zero = true;
      break;
    }
  }
  if (!found_zero) {
    // 安全回退（Base62 中 '0' 即为 0 值字符）
    zero_char = '0';
  }

  // 2. 统计输入字符串前导“零字符”的个数
  std::size_t zeros = 0;
  while (zeros < base_string.size() && base_string[zeros] == zero_char) {
    ++zeros;
  }

  // 3. 初始化大整数（big-endian，空向量表示数值 0）
  std::vector<uint8_t> bignum;

  // 4. 遍历剩余字符，进行 bignum = bignum * base + digit
  for (std::size_t i = zeros; i < base_string.size(); ++i) {
    unsigned char c = static_cast<unsigned char>(base_string[i]);
    int digit = static_cast<int>(rdata[c]);
    if (digit < 0) {
      // 包含非法字符，直接返回空表示失败
      return "";
    }

    // --- 乘法：bignum *= base ---
    if (bignum.empty()) {
      // 当前值为 0，乘 base 仍为 0，直接赋值为 digit
      if (digit > 0) {
        bignum.push_back(static_cast<uint8_t>(digit));
      }
    } else {
      int carry = 0;
      // 从低位（末尾）向高位（开头）处理
      for (int j = static_cast<int>(bignum.size()) - 1; j >= 0; --j) {
        int product = bignum[j] * 62 + carry;
        bignum[j] = static_cast<uint8_t>(product % 256);
        carry = product / 256;
      }
      // 处理乘法产生的额外进位
      while (carry > 0) {
        bignum.insert(bignum.begin(), static_cast<uint8_t>(carry % 256));
        carry /= 256;
      }

      // --- 加法：bignum += digit ---
      if (digit > 0) {
        int add_carry = digit;
        for (int j = static_cast<int>(bignum.size()) - 1;
             j >= 0 && add_carry > 0; --j) {
          int sum = bignum[j] + add_carry;
          bignum[j] = static_cast<uint8_t>(sum % 256);
          add_carry = sum / 256;
        }
        while (add_carry > 0) {
          bignum.insert(bignum.begin(), static_cast<uint8_t>(add_carry % 256));
          add_carry /= 256;
        }
      }
    }
  }

  // 5. 移除大整数前导零（保留空向量表示 0）
  while (!bignum.empty() && bignum.front() == 0) {
    bignum.erase(bignum.begin());
  }

  // 6. 构造最终二进制结果：zeros 个 0x00 + bignum 字节序列
  std::string result;
  result.reserve(zeros + bignum.size());
  result.append(zeros, '\0');
  for (uint8_t byte : bignum) {
    result.push_back(static_cast<char>(byte));
  }

  return result;
}

}  // namespace details
}  // namespace base62

namespace base62 {

/**
 * @brief 将二进制数据编码为字符串。
 * @note 若输入的二进制数据由数字类型转换而来，应注意输入的数字需为大端序。
 *
 * @tparam Alphabets 编码字符集类型，默认为 alphabet::base62。
 * @param binary_data 待编码的二进制字符串。
 * @return 编码后的字符串。
 */
template <typename Alphabets = alphabet::base62>
std::string encode(const std::string& binary_data) {
  return details::encode(binary_data, Alphabets::data());
}

/**
 * @brief 将 Base62 编码字符串解码为原始二进制数据。
 *
 * @tparam Alphabets 编码字符集类型，默认为 alphabet::base62。
 * @param base_string 待解码的字符串。
 * @return 解码后的二进制数据；若包含非法字符则返回空字符串。
 */
template <typename Alphabets = alphabet::base62>
std::string decode(const std::string& base_string) {
  return details::decode(base_string, Alphabets::rdata());
}

}  // namespace base62

}  // namespace base
}  // namespace kotucode

#endif  // !KEUNLAS_KOTUCODE_BASE_H_

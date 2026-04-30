# Kotucode's Base 项目

本项目提供了 C++ 接口的 **Base62** 和 **Base64** 相关的编解码方法。

## 功能概述

- **Base62 编解码** — 使用 0-9、A-Z、a-z 共 62 个字符进行编解码
- **Base64 编解码** — 标准 Base64 编解码支持
- **Base64URL 编解码** — URL 安全的 Base64 编解码

## 安装

本项目是纯头文件库（Header-Only），复制 include 目录下的 base.hpp 文件到你的项目中即可使用。

你也可以使用 CMake 的 FetchContent 进行导入。

```cmake
include(FetchContent)
FetchContent_Declare(base
    GIT_REPOSITORY https://github.com/kotucode/base.git
    GIT_TAG main
)
FetchContent_MakeAvailable(base)

target_link_libraries(my_app PRIVATE base)
```

## 快速开始

```cpp
#include "base.hpp"

int main() {
  auto data = "Hello World!";

  // Base62 编解码
  auto encoded = kotucode::base::base62::encode(data);
  auto decoded = kotucode::base::base62::decode(encoded);

  // Base64 编解码
  auto encoded2 = kotucode::base::base64::encode(data);
  auto decoded2 = kotucode::base::base64::decode(encoded2);

  // Base64 编解码 (url-safe)
  using base64url = kotucode::base::alphabet::base64url;
  auto encoded3 = kotucode::base::base64::encode<base64url>(data);
  auto decoded3 = kotucode::base::base64::decode<base64url>(encoded3);

  return 0;
}

```

## API 文档

项目文档由 Doxygen 生成，使用浏览器打开项目下的 `docs/html/index.html` 即可阅读文档。

## 许可证

本项目基于 MIT 许可证开源，详见 [LICENSE](https://github.com/kotucode/base) 文件。

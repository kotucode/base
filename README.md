# Kotucode's Base 项目

本项目提供了 C++ 接口的 **Base62** 和 **Base64** 相关的编解码方法。

## 功能概述

- **Base62 编解码** — 使用 0-9、A-Z、a-z 共 62 个字符进行编解码
- **Base64 编解码** — 标准 Base64 编解码支持
- **Base64URL 编解码** — URL 安全的 Base64 编解码

## 快速开始

```cpp
#include "base.hpp"

// Base62 编码
auto encoded = kotucode::base::base62::encode(data);

// Base62 解码
auto decoded = kotucode::base::base62::decode(encoded);
```

## API 文档

项目文档由 Doxygen 生成，使用浏览器打开项目下的 `docs/html/index.html` 即可阅读文档。

## 许可证

本项目基于 MIT 许可证开源，详见 [LICENSE](https://github.com/kotucode/base) 文件。

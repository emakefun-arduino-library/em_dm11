#pragma once

#ifndef _EM_DM11_LIB_H_
#define _EM_DM11_LIB_H_

/**
 * @file dm11_lib.h
 */

#include <WString.h>

namespace em {
namespace dm11_lib {
/**
 * @~Chinese
 * @brief 主版本号。
 */
/**
 * @~English
 * @brief Major version number.
 */
constexpr uint8_t kVersionMajor = 1;

/**
 * @~Chinese
 * @brief 次版本号。
 */
/**
 * @~English
 * @brief Minor version number.
 */
constexpr uint8_t kVersionMinor = 0;

/**
 * @~Chinese
 * @brief 修订版本号。
 */
/**
 * @~English
 * @brief Patch version number.
 */
constexpr uint8_t kVersionPatch = 2;

/**
 * @~Chinese
 * @brief 获取版本号字符串。
 * @return 版本号字符串，格式为 major.minor.patch。
 */
/**
 * @~English
 * @brief Get the version number string.
 * @return The version number string in the format of major.minor.patch.
 */
String Version() {
  return String(kVersionMajor) + '.' + kVersionMinor + '.' + kVersionPatch;
}
}  // namespace dm11_lib
}  // namespace em
#endif
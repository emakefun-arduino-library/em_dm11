#pragma once

#ifndef EM_I2C_TO_PWM_H_
#define EM_I2C_TO_PWM_H_

#include <WString.h>
#include <Wire.h>
#include <stdint.h>

namespace em {
class I2cToPwm {
 public:
  /**
   * @brief 主版本号。
   */
  static constexpr uint8_t kVersionMajor = 1;

  /**
   * @brief 次版本号。
   */
  static constexpr uint8_t kVersionMinor = 0;

  /**
   * @brief 修订版本号。
   */
  static constexpr uint8_t kVersionPatch = 0;

  /**
   * @brief 默认I2C地址：0x15。
   */
  static constexpr uint8_t kDefaultI2cAddress = 0x15;

  /**
   * @brief 最大PWM波频率：10000HZ
   */
  static constexpr uint16_t kMaxFrequencyHz = 10000;

  /**
   * @brief 最大PWM占空比：4095。
   */
  static constexpr uint16_t kMaxPwmDuty = 4095;

  /**
   * @brief PWM通道数：4。
   */
  static constexpr uint16_t kPwmChannelNum = 4;

  /**
   * @enum ErrorCode
   * @brief 错误码
   */
  enum ErrorCode : uint32_t {
    kOK = 0,                                  /**< 0：成功 */
    kI2cDataTooLongToFitInTransmitBuffer = 1, /**< 1：I2C数据太长，无法装入传输缓冲区 */
    kI2cReceivedNackOnTransmitOfAddress = 2,  /**< 2：在I2C发送地址时收到NACK */
    kI2cReceivedNackOnTransmitOfData = 3,     /**< 3：在I2C发送数据时收到NACK */
    kI2cOtherError = 4,                       /**< 4：其他I2C错误 */
    kI2cTimeout = 5,                          /**< 5：I2C通讯超时 */
    kInvalidParameter = 6,                    /**< 6：参数错误 */
    kUnknownError = 7,                        /**< 7：未知错误*/
  };

  /**
   * @brief 获取版本号字符串。
   * @return 版本号字符串，格式为 major.minor.patch。
   */
  static String Version() {
    return String(kVersionMajor) + '.' + kVersionMinor + '.' + kVersionPatch;
  }

  /**
   * @brief 构造函数，指定 I2C 地址和 TwoWire 对象。
   * @param i2c_address I2C 地址，默认为 @ref kDefaultI2cAddress 。
   * @param wire TwoWire 对象引用，默认为 Wire。
   */
  explicit I2cToPwm(const uint8_t i2c_address = kDefaultI2cAddress, TwoWire& wire = Wire);

  /**
   * @brief 构造函数，使用默认 I2C 地址和指定的 TwoWire 对象。
   * @param wire TwoWire 对象引用。
   */
  explicit I2cToPwm(TwoWire& wire) : I2cToPwm(kDefaultI2cAddress, wire) {
  }

  /**
   * @brief 初始化函数。
   * @param[in] frequency PWM波频率，单位HZ，范围：1 - 10000，默认为1000。
   * @return 返回值请参考 @ref ErrorCode 。
   */
  ErrorCode Init(const uint16_t frequency = 1000);

  /**
   * @brief 设置指定通道的 PWM 占空比。
   * @param[in] ch PWM通道，范围：0 - 3。
   * @param[in] duty PWM占空比，范围：0 - 4095。
   * @return 返回值请参考 @ref ErrorCode 。
   */
  ErrorCode Pwm(const uint8_t ch, uint16_t duty);

 private:
  I2cToPwm(const I2cToPwm&) = delete;
  I2cToPwm& operator=(const I2cToPwm&) = delete;

  const uint8_t i2c_address_ = kDefaultI2cAddress;
  TwoWire& wire_ = Wire;
};
}  // namespace em
#endif
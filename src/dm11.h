/**
 * @file dm11.h
 */
#pragma once

#ifndef DM11_H_
#define DM11_H_

#include <WString.h>
#include <Wire.h>
#include <stdint.h>

/**
 * @~Chinese
 * @class Dm11
 * @brief DM11是使用I2C协议驱动4路PWM从而驱动2路电机的模块，默认I2C地址为0x15。
 * @example motor_forward_backward.ino 电机前进与后退的示例
 */
/**
 * @~English
 * @class Dm11
 * @brief DM11 is a module that uses the I2C protocol to drive four PWM channels, which in turn drive two motors. The default
 * I2C address is 0x15.
 * @example motor_forward_backward.ino Example of motor forward and backward
 */
class Dm11 {
 public:
  /**
   * @~Chinese
   * @brief 主版本号。
   */
  /**
   * @~English
   * @brief Major version number.
   */
  static constexpr uint8_t kVersionMajor = 1;

  /**
   * @~Chinese
   * @brief 次版本号。
   */
  /**
   * @~English
   * @brief Minor version number.
   */
  static constexpr uint8_t kVersionMinor = 0;

  /**
   * @~Chinese
   * @brief 修订版本号。
   */
  /**
   * @~English
   * @brief Patch version number.
   */
  static constexpr uint8_t kVersionPatch = 0;

  /**
   * @~Chinese
   * @brief 默认I2C地址。
   */
  /**
   * @~English
   * @brief Default I2C address.
   */
  static constexpr uint8_t kDefaultI2cAddress = 0x15;

  /**
   * @~Chinese
   * @brief 最小PWM波频率。
   */
  /**
   * @~English
   * @brief Minimum PWM wave frequency.
   */
  static constexpr uint16_t kMinFrequencyHz = 1;

  /**
   * @~Chinese
   * @brief 最大PWM波频率。
   */
  /**
   * @~English
   * @brief Maximum PWM wave frequency.
   */
  static constexpr uint16_t kMaxFrequencyHz = 10000;

  /**
   * @~Chinese
   * @brief 最大PWM占空比。
   */
  /**
   * @~English
   * @brief Maximum PWM duty cycle.
   */
  static constexpr uint16_t kMaxPwmDuty = 4095;

  /**
   * @~Chinese
   * @brief PWM通道数。
   */
  /**
   * @~English
   * @brief Number of PWM channels.
   */
  static constexpr uint16_t kPwmChannelNum = 4;

  /**
   * @~Chinese
   * @enum ErrorCode
   * @brief 错误码。
   */
  /**
   * @~English
   * @enum ErrorCode
   * @brief Error codes.
   */
  enum ErrorCode : uint32_t {
    /**
     * @~Chinese
     * @brief 0：成功。
     */
    /**
     * @~English
     * @brief 0: Success.
     */
    kOK = 0,

    /**
     * @~Chinese
     * @brief 1：I2C数据太长，无法装入传输缓冲区。
     */
    /**
     * @~English
     * @brief 1: I2C data too long to fit in transmit buffer.
     */
    kI2cDataTooLongToFitInTransmitBuffer = 1,

    /**
     * @~Chinese
     * @brief 2：在I2C发送地址时收到NACK。
     */
    /**
     * @~English
     * @brief 2: NACK received on I2C transmit of address.
     */
    kI2cReceivedNackOnTransmitOfAddress = 2,

    /**
     * @~Chinese
     * @brief 3：在I2C发送数据时收到NACK。
     */
    /**
     * @~English
     * @brief 3: NACK received on I2C transmit of data.
     */
    kI2cReceivedNackOnTransmitOfData = 3,

    /**
     * @~Chinese
     * @brief 4：其他I2C错误。
     */
    /**
     * @~English
     * @brief 4: Other I2C errors.
     */
    kI2cOtherError = 4,

    /**
     * @~Chinese
     * @brief 5：I2C通讯超时。
     */
    /**
     * @~English
     * @brief 5: I2C communication timed out.
     */
    kI2cTimeout = 5,

    /**
     * @~Chinese
     * @brief 6：参数错误。
     */
    /**
     * @~English
     * @brief 6: Invalid parameter.
     */
    kInvalidParameter = 6,

    /**
     * @~Chinese
     * @brief 7：未知错误。
     */
    /**
     * @~English
     * @brief 7: Unknown error.
     */
    kUnknownError = 7,
  };

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
  static String Version() {
    return String(kVersionMajor) + '.' + kVersionMinor + '.' + kVersionPatch;
  }

  /**
   * @~Chinese
   * @brief 构造函数，指定 I2C 地址和 TwoWire 对象。
   * @param i2c_address I2C 地址，默认为 @ref kDefaultI2cAddress 。
   * @param wire TwoWire 对象引用，默认为 Wire。
   */
  /**
   * @~English
   * @brief Constructor, specifying I2C address and TwoWire object.
   * @param i2c_address I2C address, defaults to @ref kDefaultI2cAddress.
   * @param wire TwoWire object reference, defaults to Wire.
   */
  explicit Dm11(const uint8_t i2c_address = kDefaultI2cAddress, TwoWire& wire = Wire);

  /**
   * @~Chinese
   * @brief 构造函数，使用默认 I2C 地址和指定的 TwoWire 对象。
   * @param wire TwoWire 对象引用。
   */
  /**
   * @~English
   * @brief Constructor using the default I2C address and a specified TwoWire object.
   * @param wire TwoWire object reference.
   */
  explicit Dm11(TwoWire& wire) : Dm11(kDefaultI2cAddress, wire) {
  }

  /**
   * @~Chinese
   * @brief 初始化函数。
   * @param[in] frequency_hz PWM波频率，单位HZ，范围：1 ~ 10000，默认为1000。
   * @return 返回值请参考 @ref ErrorCode 。
   */
  /**
   * @~English
   * @brief Initialization function.
   * @param[in] frequency_hz PWM wave frequency in Hz, range: 1 ~ 10000, default is 1000.
   * @return Return value please refer to @ref ErrorCode.
   */
  ErrorCode Init(const uint16_t frequency_hz = 1000);

  /**
   * @~Chinese
   * @brief 设置指定通道的 PWM 占空比。
   * @param[in] ch PWM通道，范围：0 ~ 3。
   * @param[in] duty PWM占空比，范围：0 ~ 4095。
   * @return 返回值请参考 @ref ErrorCode 。
   */
  /**
   * @~English
   * @brief Set the PWM duty cycle for a specified channel.
   * @param[in] ch PWM channel, range: 0 ~ 3.
   * @param[in] duty PWM duty cycle, range: 0 ~ 4095.
   * @return Return value please refer to @ref ErrorCode.
   */
  ErrorCode Pwm(const uint8_t ch, uint16_t duty);

 private:
  Dm11(const Dm11&) = delete;
  Dm11& operator=(const Dm11&) = delete;

  const uint8_t i2c_address_ = kDefaultI2cAddress;
  TwoWire& wire_ = Wire;
};
#endif
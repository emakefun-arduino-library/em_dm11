#pragma once

#ifndef DM11_H_
#define DM11_H_

#include <WString.h>
#include <Wire.h>
#include <stdint.h>

class Dm11 {
 public:
  /**
   * @cond Chinese
   * @brief 主版本号。
   * @endcond
   */
  /**
   * @cond English
   * @brief Major version number.
   * @endcond
   */
  static constexpr uint8_t kVersionMajor = 1;

  /**
   * @cond Chinese
   * @brief 次版本号。
   * @endcond
   */
  /**
   * @cond English
   * @brief Minor version number.
   * @endcond
   */
  static constexpr uint8_t kVersionMinor = 0;

  /**
   * @cond Chinese
   * @brief 修订版本号。
   * @endcond
   */
  /**
   * @cond English
   * @brief Patch version number.
   * @endcond
   */
  static constexpr uint8_t kVersionPatch = 0;

  /**
   * @cond Chinese
   * @brief 默认I2C地址。
   * @endcond
   */
  /**
   * @cond English
   * @brief Default I2C address.
   * @endcond
   */
  static constexpr uint8_t kDefaultI2cAddress = 0x15;

  /**
   * @cond Chinese
   * @brief 最小PWM波频率。
   * @endcond
   */
  /**
   * @cond English
   * @brief Minimum PWM wave frequency.
   * @endcond
   */
  static constexpr uint16_t kMinFrequencyHz = 1;

  /**
   * @cond Chinese
   * @brief 最大PWM波频率。
   * @endcond
   */
  /**
   * @cond English
   * @brief Maximum PWM wave frequency.
   * @endcond
   */
  static constexpr uint16_t kMaxFrequencyHz = 10000;

  /**
   * @cond Chinese
   * @brief 最大PWM占空比。
   * @endcond
   */
  /**
   * @cond English
   * @brief Maximum PWM duty cycle.
   * @endcond
   */
  static constexpr uint16_t kMaxPwmDuty = 4095;

  /**
   * @cond Chinese
   * @brief PWM通道数。
   * @endcond
   */
  /**
   * @cond English
   * @brief Number of PWM channels.
   * @endcond
   */
  static constexpr uint16_t kPwmChannelNum = 4;

  /**
   * @cond Chinese
   * @enum ErrorCode
   * @brief 错误码。
   * @endcond
   */
  /**
   * @cond English
   * @enum ErrorCode
   * @brief Error codes.
   * @endcond
   */
  enum ErrorCode : uint32_t {
    /**
     * @cond Chinese
     * @brief 0：成功。
     * @endcond
     */
    /**
     * @cond English
     * @brief 0: Success.
     * @endcond
     */
    kOK = 0,

    /**
     * @cond Chinese
     * @brief 1：I2C数据太长，无法装入传输缓冲区。
     * @endcond
     */
    /**
     * @cond English
     * @brief 1: I2C data too long to fit in transmit buffer.
     * @endcond
     */
    kI2cDataTooLongToFitInTransmitBuffer = 1,

    /**
     * @cond Chinese
     * @brief 2：在I2C发送地址时收到NACK。
     * @endcond
     */
    /**
     * @cond English
     * @brief 2: NACK received on I2C transmit of address.
     * @endcond
     */
    kI2cReceivedNackOnTransmitOfAddress = 2,

    /**
     * @cond Chinese
     * @brief 3：在I2C发送数据时收到NACK。
     * @endcond
     */
    /**
     * @cond English
     * @brief 3: NACK received on I2C transmit of data.
     * @endcond
     */
    kI2cReceivedNackOnTransmitOfData = 3,

    /**
     * @cond Chinese
     * @brief 4：其他I2C错误。
     * @endcond
     */
    /**
     * @cond English
     * @brief 4: Other I2C errors.
     * @endcond
     */
    kI2cOtherError = 4,

    /**
     * @cond Chinese
     * @brief 5：I2C通讯超时。
     * @endcond
     */
    /**
     * @cond English
     * @brief 5: I2C communication timed out.
     * @endcond
     */
    kI2cTimeout = 5,

    /**
     * @cond Chinese
     * @brief 6：参数错误。
     * @endcond
     */
    /**
     * @cond English
     * @brief 6: Invalid parameter.
     * @endcond
     */
    kInvalidParameter = 6,

    /**
     * @cond Chinese
     * @brief 7：未知错误。
     * @endcond
     */
    /**
     * @cond English
     * @brief 7: Unknown error.
     * @endcond
     */
    kUnknownError = 7,
  };

  /**
   * @cond Chinese
   * @brief 获取版本号字符串。
   * @return 版本号字符串，格式为 major.minor.patch。
   * @endcond
   */
  /**
   * @cond English
   * @brief Get the version number string.
   * @return The version number string in the format of major.minor.patch.
   * @endcond
   */
  static String Version() {
    return String(kVersionMajor) + '.' + kVersionMinor + '.' + kVersionPatch;
  }

  /**
   * @cond Chinese
   * @brief 构造函数，指定 I2C 地址和 TwoWire 对象。
   * @param i2c_address I2C 地址，默认为 @ref kDefaultI2cAddress 。
   * @param wire TwoWire 对象引用，默认为 Wire。
   * @endcond
   */
  /**
   * @cond English
   * @brief Constructor, specifying I2C address and TwoWire object.
   * @param i2c_address I2C address, defaults to @ref kDefaultI2cAddress.
   * @param wire TwoWire object reference, defaults to Wire.
   * @endcond
   */
  explicit Dm11(const uint8_t i2c_address = kDefaultI2cAddress, TwoWire& wire = Wire);

  /**
   * @cond Chinese
   * @brief 构造函数，使用默认 I2C 地址和指定的 TwoWire 对象。
   * @param wire TwoWire 对象引用。
   * @endcond
   */
  /**
   * @cond English
   * @brief Constructor using the default I2C address and a specified TwoWire object.
   * @param wire TwoWire object reference.
   * @endcond
   */
  explicit Dm11(TwoWire& wire) : Dm11(kDefaultI2cAddress, wire) {
  }

  /**
   * @cond Chinese
   * @brief 初始化函数。
   * @param[in] frequency_hz PWM波频率，单位HZ，范围：1 ~ 10000，默认为1000。
   * @return 返回值请参考 @ref ErrorCode 。
   * @endcond
   */
  /**
   * @cond English
   * @brief Initialization function.
   * @param[in] frequency_hz PWM wave frequency in Hz, range: 1 ~ 10000, default is 1000.
   * @return Return value please refer to @ref ErrorCode.
   * @endcond
   */
  ErrorCode Init(const uint16_t frequency_hz = 1000);

  /**
   * @cond Chinese
   * @brief 设置指定通道的 PWM 占空比。
   * @param[in] ch PWM通道，范围：0 ~ 3。
   * @param[in] duty PWM占空比，范围：0 ~ 4095。
   * @return 返回值请参考 @ref ErrorCode 。
   * @endcond
   */
  /**
   * @cond English
   * @brief Set the PWM duty cycle for a specified channel.
   * @param[in] ch PWM channel, range: 0 ~ 3.
   * @param[in] duty PWM duty cycle, range: 0 ~ 4095.
   * @return Return value please refer to @ref ErrorCode.
   * @endcond
   */
  ErrorCode Pwm(const uint8_t ch, uint16_t duty);

 private:
  Dm11(const Dm11&) = delete;
  Dm11& operator=(const Dm11&) = delete;

  const uint8_t i2c_address_ = kDefaultI2cAddress;
  TwoWire& wire_ = Wire;
};
#endif
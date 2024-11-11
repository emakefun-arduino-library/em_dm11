#pragma once

#ifndef EM_I2C_DUAL_MOTOR_H_
#define EM_I2C_DUAL_MOTOR_H_

#include <WString.h>
#include <Wire.h>
#include <stdint.h>

namespace em {
class I2cDualMotor {
 public:
  static constexpr uint8_t kVersionMajor = 1;
  static constexpr uint8_t kVersionMinor = 0;
  static constexpr uint8_t kVersionPatch = 0;
  static constexpr uint8_t kDefaultI2cAddress = 0x15;
  static constexpr uint16_t kMaxPwmDuty = 4095;

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

  enum Channel : uint8_t {
    kCh0 = 0,
    kCh1,
    kCh2,
    kCh3,
  };

  static String Version() {
    return String(kVersionMajor) + '.' + kVersionMinor + '.' + kVersionPatch;
  }

  explicit I2cDualMotor(const uint8_t i2c_address = kDefaultI2cAddress, TwoWire& wire = Wire);

  explicit I2cDualMotor(TwoWire& wire) : I2cDualMotor(kDefaultI2cAddress, wire) {
  }

  /**
   * @brief 初始化函数
   * @return 返回值请参考 @ref ErrorCode
   */
  ErrorCode Init(const uint32_t frequency = 1000 * 1000);

  ErrorCode Pwm(const Channel, uint16_t duty);

 private:
  I2cDualMotor(const I2cDualMotor&) = delete;
  I2cDualMotor& operator=(const I2cDualMotor&) = delete;

  const uint8_t i2c_address_ = kDefaultI2cAddress;
  TwoWire& wire_ = Wire;
};
}  // namespace em
#endif
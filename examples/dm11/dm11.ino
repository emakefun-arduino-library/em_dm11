/**
 * @example dm11.ino
 */

#include "dm11.h"

namespace {
Dm11 g_dm11;
}

void setup() {
  Serial.begin(115200);
  Serial.println("setup");
  Serial.println(String("lib version: ") + Dm11::Version());

  Wire.begin();

  const auto ret = g_dm11.Init();

  if (Dm11::kOK == ret) {
    Serial.println("i2c to pwm initialization successful");
  } else {
    Serial.print("i2c to pwm initialization failed: ");
    Serial.println(ret);
    while (true);
  }

  Serial.println(F("setup successful"));
}

void loop() {
  g_dm11.Pwm(0, 0);
  g_dm11.Pwm(1, 4095);
  g_dm11.Pwm(2, 0);
  g_dm11.Pwm(3, 4095);
  Serial.println("F");
  delay(1000);

  g_dm11.Pwm(0, 4095);
  g_dm11.Pwm(1, 0);
  g_dm11.Pwm(2, 4095);
  g_dm11.Pwm(3, 0);
  Serial.println("B");
  delay(1000);
}

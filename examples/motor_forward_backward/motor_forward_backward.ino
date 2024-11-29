#include "dm11.h"

static em::Dm11 g_dm11;

void setup() {
  Serial.begin(115200);
  Serial.println("setup");
  Serial.println(String("dm11 lib version: ") + em::Dm11::Version());

  Wire.begin();

  const auto ret = g_dm11.Init();

  if (em::Dm11::kOK == ret) {
    Serial.println("dm11 initialization successful");
  } else {
    Serial.print("dm11 initialization failed: ");
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
  Serial.println("motor forward");
  delay(1000);

  g_dm11.Pwm(0, 4095);
  g_dm11.Pwm(1, 0);
  g_dm11.Pwm(2, 4095);
  g_dm11.Pwm(3, 0);
  Serial.println("motor backward");
  delay(1000);
}

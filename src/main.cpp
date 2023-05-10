#include <Arduino.h>
#include <esp32-hal-timer.h>
hw_timer_t *timer = NULL;

uint32_t count = 0;
void IRAM_ATTR onTimer()
{
  Serial.println("Timer");
}

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  timer = timerBegin(0, 80, true);
  timerAttachInterrupt(timer, &onTimer, true);
  timerAlarmWrite(timer, 1000000, true);
  timerAlarmEnable(timer);
  timerStart(timer);
}

void loop()
{
  // put your main code here, to run repeatedly:
  delay(1000);
  count = timerGetConfig(timer);
  Serial.println(count);
  Serial.println(String(timerRead(timer)));
}
#include <RH_ASK.h>
#include <SPI.h> // Required even if not used

RH_ASK driver;  // Defaults to pin 12

const int btn1 = 2, btn2 = 3, btn3 = 4, btn4 = 5;

void setup() {
  pinMode(btn1, INPUT_PULLUP);
  pinMode(btn2, INPUT_PULLUP);
  pinMode(btn3, INPUT_PULLUP);
  pinMode(btn4, INPUT_PULLUP);

  if (!driver.init()) {
    // Initialization failed
    while (1); 
  }
}

void loop() {
  char cmd = 'N';  // Default: No command

  if (digitalRead(btn1) == LOW) cmd = 'R';   // Servo Right
  else if (digitalRead(btn2) == LOW) cmd = 'L'; // Servo Left
  else if (digitalRead(btn3) == LOW) cmd = 'F'; // Stepper CW
  else if (digitalRead(btn4) == LOW) cmd = 'B'; // Stepper CCW

  driver.send((uint8_t *)&cmd, 1);
  driver.waitPacketSent();
  delay(50);
}

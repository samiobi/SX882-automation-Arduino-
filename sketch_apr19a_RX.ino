
#include <RH_ASK.h>
#include <SPI.h>
#include <ServoTimer2.h>
#include <Stepper.h>

RH_ASK driver;

ServoTimer2 myServo;
const int servoPin = 9;

const int stepsPerRevolution = 2000;
Stepper myStepper(stepsPerRevolution, 2, 4, 3, 5);

char command = 'N';

// Converts angle in degrees (0° to 180°) to microseconds (500 to 2400)
int degreesToMicros(int angle) {
  return map(angle, 0, 180, 500, 2400);
}

void setup() {
  myServo.attach(servoPin);
  myServo.write(degreesToMicros(90));  // Center position

  if (!driver.init()) {
    while (1); // Halt if RF not initialized
  }
}

void loop() {
  uint8_t buf[1];
  uint8_t buflen = sizeof(buf);

  if (driver.recv(buf, &buflen)) {
    command = (char)buf[0];
  }

  switch (command) {
    case 'R':
      myServo.write(degreesToMicros(0)); // Right
      break;
    case 'L':
      myServo.write(degreesToMicros(180));  // Left
      break;
    case 'F':
      myStepper.step(1);  // Stepper CW
      break;
    case 'B':
      myStepper.step(-1); // Stepper CCW
      break;
    default:
      myServo.write(degreesToMicros(90)); // Return to center
      break;
  }

  delay(10);
}

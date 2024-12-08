#include <Stepper.h>

const int stepsPerRevolution = 2048;  // change this to fit the number of steps per revolution

// ULN2003 Motor Driver Pins
#define IN1 19
#define IN2 18
#define IN3 5
#define IN4 17

// initialize the stepper library
Stepper myStepper(stepsPerRevolution, IN1, IN3, IN2, IN4);

// Function to move the stepper motor by a specified angle in degrees
void moveStepperByAngle(float angle) {
  int steps = (stepsPerRevolution * angle) / 360;
  myStepper.step(steps);
}

void setup() {
  // set the speed at 5 rpm
  myStepper.setSpeed(20);
  // initialize the serial port
  Serial.begin(115200);
}

void loop() {
  // step 50.2 degrees in one direction:
  Serial.println("clockwise 50.2 degrees");
  moveStepperByAngle(50.2);
  delay(1000);

  // step 50.2 degrees in the other direction:
  Serial.println("counterclockwise 50.2 degrees");
  moveStepperByAngle(-50.2);
  delay(1000);
}

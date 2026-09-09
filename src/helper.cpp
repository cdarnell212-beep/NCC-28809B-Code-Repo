#include "vex.h"
#include "robot-config.h"
using namespace vex;
#include <string> 

int angle = 0;
int rotation = 0;

bool flipped = true;
bool tilted = true;

void printRotation(motor &clawMotorLeft, motor &clawMotorRight) {
  Brain.Screen.clearLine(2);
  Brain.Screen.setCursor(2, 1);
  Brain.Screen.print("L: %.0f  R: %.0f",
                     clawMotorLeft.position(rotationUnits::deg),
                     clawMotorRight.position(rotationUnits::deg));

}

void changeAngleFor(int angle, vex::directionType dir) {
  int signedAngle = (dir == vex::directionType::fwd) ? angle : -angle;
  clawMotorLeft.spinFor(signedAngle, degrees, false);
  clawMotorRight.spinFor(signedAngle, degrees, false);
}

void changeRotationFor(int angle, vex::directionType dir) {
  int signedAngle = (dir == vex::directionType::fwd) ? angle : -angle;
  clawMotorLeft.spinFor(-signedAngle, degrees, false);
  clawMotorRight.spinFor(signedAngle, degrees, false);
}

void changeAngle(vex::directionType dir) {
  clawMotorLeft.spin(dir);
  clawMotorRight.spin(dir);
}

void changeRotation(vex::directionType dir) {
  clawMotorLeft.spin(dir, -100, pct);
  clawMotorRight.spin(dir, 100, pct);
}

void stopMotors() {
  clawMotorLeft.stop();
  clawMotorRight.stop();
}

void flipClaw() {
  int angle = 113;
  if (flipped) {
    changeRotationFor(angle, directionType::rev);
    flipped = false;
  } else {
    changeRotationFor(angle, directionType::fwd);
    flipped = true;
  }
}

void tiltClaw() {
  int angle = 45;
  if (tilted) {
    changeAngleFor(angle, directionType::fwd);
    tilted = false;
  } else {
    changeAngleFor(angle, directionType::rev);
    tilted = true;
  }
}



int oneDirection_control(motor &m, vex::controller::button &btn, vex::directionType dir, double power) {
  while (1) {
    if (btn.pressing()) {
      m.spin(dir, power, pct);
    } else {
      m.stop();
    }
    wait(20, msec);
  }
  return 0;
}

int twoDirection_control(motor &m, vex::controller::button &btn1, vex::controller::button &btn2) {
  while (1) {
    if (btn1.pressing()) {
      m.spin(forward);
    } else if (btn2.pressing()) {
      m.spin(reverse);
    } else {
      m.stop();
    }
    wait(20, msec);
  }
  return 0;
}

int pnumatic_toggle(vex::controller::button &btn, vex::digital_out &p) {
  bool state = false;
  while (1) {
    if (btn.pressing()) {
      state = !state;
      p.set(state);
      wait(500, msec);
    }
    wait(20, msec);
  }
  return 0;
}


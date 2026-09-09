#pragma once
#include "JAR-Template/drive.h"
using namespace vex;

void printRotation(motor &clawMotorLeft, motor &clawMotorRight);
void changeAngleFor(int angle, vex::directionType dir);
void changeRotationFor(int angle, vex::directionType dir);
void changeAngle(vex::directionType dir);
void changeRotation(vex::directionType dir);
void stopMotors();
void flipClaw();
void tiltClaw();
int rotation_control();
int oneDirection_control();
int twoDirection_control();
int pnumatic_toggle();

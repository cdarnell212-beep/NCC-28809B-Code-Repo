using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern drivetrain Drivetrain;
extern motor clawMotorLeft;
extern motor clawMotorRight;
extern inertial Inertial5;
extern motor leftMotorA;
extern motor leftMotorB;
extern motor rightMotorA;
extern motor rightMotorB;
extern motor liftleft;
extern motor liftright;
extern digital_out DigitalOutA;
extern motor_group liftgroup;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit(void);
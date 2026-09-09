#include "vex.h"

/**
 * Resets the constants for auton movement.
 * Modify these to change the default behavior of functions like
 * drive_distance(). For explanations of the difference between
 * drive, heading, turning, and swinging, as well as the PID and
 * exit conditions, check the docs.
 */



int print(){
  while (true){
    Controller1.Screen.print(Inertial5.heading());
    Controller1.Screen.setCursor(1, 1);
    wait(50, msec);
  }
  return 0;
}

//add this to the first line of ur auton
//      new task(print);

void TestOne(){

  // Sets the max voltage for driving to 10 volts. This can be adjusted to make 
  // the robot drive slower or faster. Use Values between 1 to 12
  chassis.drive_max_voltage = 10;
  
  // Drives forward 32 inches using PID
  chassis.drive_distance(32.0);

  // Activates pneumatics
  DigitalOutA.set(true);

  //Sets the velosity of the lift motors to 50 percent
  liftgroup.setVelocity(50, percent);

  // Moves your Double Reverse Four Bar (DR4B) up
  liftgroup.spinFor(fwd, 10, degrees);

  // Drives in reverse 17 inches
  chassis.drive_distance(-17.0);

  // Turns to an absolute heading of 90 degrees
  chassis.turn_to_angle(90.0);

  // Drives forward 15 inches
  chassis.drive_distance(15.0);

  // Deactivates pneumatics
  DigitalOutA.set(false);

  // Moves the DR4B back down
    liftgroup.spinFor(reverse, 10, degrees);


}

void OdoTest() {

  // Starting position: x, y, heading 0
  chassis.set_coordinates(-62, 0, 0);

  //Drive to point in inches 
  chassis.drive_to_point(-33, 0);

  // Turn to face point in inches
  chassis.turn_to_point(-24, -24);

  // Drive to x=0, y=0 and finish facing 180 degrees
  chassis.drive_to_pose(-24, -24, 180);
}
/**
 * The expected behavior is to return to the start angle, after making a complete turn.
 */

void turn_test(){
  chassis.turn_to_angle(5);
  chassis.turn_to_angle(30);
  chassis.turn_to_angle(90);
  chassis.turn_to_angle(225);
  chassis.turn_to_angle(0);
}



void default_constants(){
  // Each constant set is in the form of (maxVoltage, kP, kI, kD, startI).
  
  chassis.set_drive_constants(10, 1.5, 0, 10, 0);
  chassis.set_heading_constants(6, .4, 0, 1, 0);
  chassis.set_turn_constants(12, .4, .03, 3, 15);
  chassis.set_swing_constants(12, .3, .001, 2, 15);

  // Each exit condition set is in the form of (settle_error, settle_time, timeout).
  chassis.set_drive_exit_conditions(1.5, 300, 5000);
  chassis.set_turn_exit_conditions(1, 300, 3000);
  chassis.set_swing_exit_conditions(1, 300, 3000);
}

/**
 * Sets constants to be more effective for odom movements.
 * For functions like drive_to_point(), it's often better to have
 * a slower max_voltage and greater settle_error than you would otherwise.
 */

void odom_constants(){
  default_constants();
  chassis.heading_max_voltage = 10;
  chassis.drive_max_voltage = 8;
  chassis.drive_settle_error = 3;
  chassis.boomerang_lead = .5;
  chassis.drive_min_voltage = 0;
}


void myAuto(){


}

void drive_test() {


}
/**
 * Should swing in a fun S shape.
 */

void swing_test(){
  chassis.left_swing_to_angle(90);
  chassis.right_swing_to_angle(0);
}

/**
 * A little of this, a little of that; it should end roughly where it started.
 */

void full_test(){
  new task (print);
  chassis.drive_distance(24);
  chassis.turn_to_angle(-45);
  chassis.drive_distance(-36);
  chassis.right_swing_to_angle(-90);
  chassis.drive_distance(24);
  chassis.turn_to_angle(0);
}

/**
 * Doesn't drive the robot, but just prints coordinates to the Brain screen 
 * so you can check if they are accurate to life. Push the robot around and
 * see if the coordinates increase like you'd expect.
 */

void odom_test(){
  chassis.set_coordinates(0, 0, 0);
  while(1){
    Brain.Screen.clearScreen();
    Brain.Screen.printAt(5,20, "X: %f", chassis.get_X_position());
    Brain.Screen.printAt(5,40, "Y: %f", chassis.get_Y_position());
    Brain.Screen.printAt(5,60, "Heading: %f", chassis.get_absolute_heading());
    Brain.Screen.printAt(5,80, "ForwardTracker: %f", chassis.get_ForwardTracker_position());
    Brain.Screen.printAt(5,100, "SidewaysTracker: %f", chassis.get_SidewaysTracker_position());
    task::sleep(20);
  }
}

/**
 * Should end in the same place it began, but the second movement
 * will be curved while the first is straight.
 */

void tank_odom_test(){
  odom_constants();
  chassis.set_coordinates(0, 0, 0);
  chassis.turn_to_point(24, 24);
  chassis.drive_to_point(24,24);
  chassis.drive_to_point(0,0);
  chassis.turn_to_angle(0);
}

/**
 * Drives in a square while making a full turn in the process. Should
 * end where it started.
 */

void holonomic_odom_test(){
  odom_constants();
  chassis.set_coordinates(0, 0, 0);
  chassis.holonomic_drive_to_pose(0, 18, 90);
  chassis.holonomic_drive_to_pose(18, 0, 180);
  chassis.holonomic_drive_to_pose(0, 18, 270);
  chassis.holonomic_drive_to_pose(0, 0, 0);
}
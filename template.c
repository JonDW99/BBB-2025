#include <kipr/wombat.h>
#include <stdio.h>

// Attaching values to words for later use //
#define clawArm 0
#define clawWrist 1
#define clawHand 2
#define leftM 0
#define rightM 3
#define leftS analog(4)
#define rightS analog(5)

// Simplying the servo  command //
void servo(float port, float position){
  set_servo_position(port, position);
}

// Function dedicated for a pause (in seconds) //
void wait(float time){
  motor(leftM, 0);  // Stops left wheel movement 
  motor(rightM, 0);  // Stops right wheel movement
  msleep(time * 1000);  // Amount of time that the movement is stopped
}

// Function used when driving straight //
void driveS(float speed, float distance){
  clear_motor_position_counter(0);  // Resets the left wheel distance tracker
  while (get_motor_position_counter(0) < distance){  // Runs the below code until the left distance value has been reached
    motor(leftM, speed);  // Runs the left wheel at set speed
    motor(rightM, speed);  // Runs the right wheel at set speed
  }
}

// Function used when not driving straight //
void steer(float speedL, float speedR, float distance){
  clear_motor_position_counter(0);  // Resets the left wheel distance tracker
  while (get_motor_position_counter(0) < distance){  // Runs the below code until the left distance value has been reached
    motor(leftM, speedL);  // Runs the left wheel at desired left wheel speed
    motor(rightM, speedR); // Runs the right wheel at desired right wheel speed
  }
}

// Function used to turn (+degrees = left; -degrees = right;)  //
void turn(float degrees){
  clear_motor_position_counter(0);  // Resets the left wheel distance tracker
  clear_motor_position_counter(3);  // Resets the right wheel distance tracker
  if (degrees > 0){  // Runs the below code if degrees are + (left turn)
    degrees = degrees * 11.6;  // Converts the degrees into a distance value
    while (get_motor_position_counter(3) < degrees){  // Runs the below code until calculated distance value has been reached
      motor(leftM, -50);  // Runs the left wheel backwards
      motor(rightM, 50);  // Runs the right wheel forwards
    }
  }
  else if (degrees < 0){  // Runs the below code if degrees are - (right turn)
    degrees = degrees * -11.6;  // Converts the degrees into a distance value
    while (get_motor_position_counter(0) < degrees){   // Runs the below code until calculated distance value has been reached
      motor(leftM, 50);  // Runs the left wheel forwards  
      motor(rightM, -50); // Runs the right wheel backwards
    }
  }
}

// Function used to slowly move a servo //
void slowServo(float port, float position){
  if (get_servo_position(port) < position){  // If the current servo position is less than the desired servo position (moves servo up)
    while (get_servo_position(port) < position){  // Runs below code until desired servo position has been reached
      float newPos = get_servo_position(port) + 2;  // Set next servo position to 2 greater than previous
      servo(port, newPos);  // Move the servo to this next servo position
      msleep(4);  // Wait 4 miliseconds
    }
  }
  else if (get_servo_position(port) > position){  // If the current servo position is greater than the desired servo position (moves servo down)
    while (get_servo_position(port) > position){  // Runs below code until desired servo position has been reached
      float newPos = get_servo_position(port) - 2;  // Set next servo position to 2 less than previous
      servo(port, newPos);  // Move the servo to this next servo position
      msleep(4);  // Wait 4 miliseconds
    }
  }
}

// Function used to follow a black line for a certain distance //
void lineFollow(float speed, float distance){
  clear_motor_position_counter(0);  // Resets the left wheel distance tracker
  clear_motor_position_counter(3);  // Resets the right wheel distance tracker
  int averagePos;  // Creates the variable that later calculates the average distance traveled by both wheels
  while (averagePos < distance){  // Runs below code until the desired distance has been reached
     if ((leftS > 3628) && (rightS > 3628)){  // If the left and right sensor detect black
      motor(leftM, speed * .9);  // Runs the left wheel at .9 speed
      motor(rightM, speed * .9); // Runs the right wheel at .9 speed
     }
     else if (leftS > 3600){  // If only the left sensor detects black
      motor(leftM, speed*.35);  // Runs the left wheel at .35 speed
      motor(rightM, speed);  // Runs the right wheel at full desired speed
    }
    else if (rightS > 3600){  // If only the right sensor detects black
      motor(leftM, speed);  // Runs the left wheel at full desired speed
      motor(rightM, speed*.35);  // Runs the right wheel at .35 speed
    }
    else{  // If neither sensors detect black
       motor(leftM, speed*.9);  // Runs the left wheel at .9 speed
       motor(rightM, speed*.35);  // Runs the right wheel at .35 speed
    }
     averagePos = (get_motor_position_counter(0) + get_motor_position_counter(3)) / 2;  // Recalculates the average distance
  }
}

// Enter functions you would like the robot to run //
int main()
{
  //wait_for_light(0);
  //shut_down_in(119);
  	console_clear();
    
  return 0;
}

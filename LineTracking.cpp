#include "LineTracking.hpp"

// //[added:
// // PID Constants (Tune these values based on testing)
// #define Kp 30.0   // Proportional gain
// #define Ki 0.05   // Integral gain
// #define Kd 30.0   // Derivative gain
// // PID variables
// float integral = 0;
// float prevError = 0;
// unsigned long prevTime = 0;
// //:added]

void LineTracking::FollowingLine( uint8_t Case, uint16_t Speed ){
  // Calculate time difference
  // unsigned long currentTime = millis();
  // float dt = (currentTime - prevTime) / 1000.0f; // Convert to seconds
  // prevTime = currentTime;

  // // Calculate error from IR sensors
  // float error = 0;

  switch (Case)
  {
  /*Change the Motion::ACTION for each case or Motor::Syop() for stop*/
  case OnTrack:
    Motion::Forwards(Speed);
    //error=0.0;
    delay(5); //You may change the delay duration 
    //31/3changed: delay(1)-->delay(10)
  break;

  case SlowOnTrack:
    Motion::Forwards(Speed);
    delay(5);
  break;

  case IR_LOnTrack:
    Motion::Leftwards(Speed); //Leftwards
    //error=20.0;
    delay(20); //You may change the delay duration 30
  break;

  case IR_ROnTrack:
    Motion::Rightwards(Speed); //Rightwards
    //error=-20.0;
    delay(5); //You may change the delay duration //50 30 10
  break;

  case AllOnTrack:
    Motor::Stop();
    delay(5); //You may change the delay duration 
  break;
  
  case IR_LandROnTrack:
    Motion::Forwards(Speed);
    //error = (prevError > 0) ? 2.0 : -2.0; // Aggressive correction
    delay(5); //You may change the delay duration 
  break;

  case OutOfTrack:
    Motion::Backwards(Speed);
    //error = prevError * 1.2; // Gradually increase correction
    delay(5); //You may change the delay duration 
  break;

  // default:
  //   error=0.0;
  }

  //PID calculations
  // integral += error * dt;
  // float derivative = (error - prevError) / dt;
  // float output = (Kp * error) + (Ki * integral) + (Kd * derivative);
  // prevError = error;

  // // Adjust motor speeds
  // int16_t leftSpeed = Speed + output;
  // int16_t rightSpeed = Speed - output;

  // // Limit speeds to valid PWM range (0-1024)
  // leftSpeed = constrain(leftSpeed, 0, 1024);
  // rightSpeed = constrain(rightSpeed, 0, 1024);

  // // Apply speeds to motors
  // Motor::Moving_AntiClockwise(leftSpeed, LeftWheel);
  // Motor::Moving_AntiClockwise(rightSpeed, RightWheel);

  // // Optional: Keep servo neutral if using differential steering
  // Servo::TrunDeg(90);
};
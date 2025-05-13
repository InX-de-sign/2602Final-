#include "LineTracking.hpp"

void LineTracking::FollowingLine( uint8_t Case, uint16_t Speed ){
  switch (Case)
  {
  /*Change the Motion::ACTION for each case or Motor::Syop() for stop*/
  case OutOfTrack:
    Motion::Backwards(Speed);
    delay(5); 
  break;

  case OnTrack:
    Motion::Forwards(Speed);
    // Serial.println("111");
    delay(5);  
    //31/3changed: delay(1)-->delay(10)
  break;

  case IR_LOnTrack:
    Motion::Leftwards(Speed); //Leftwards
    delay(20); //You may change the delay duration 30
  break;

  case IR_ROnTrack:
    Motion::Rightwards(Speed); //Rightwards
    delay(5); //You may change the delay duration //50 30 10
  break;

  case AllOnTrack:
    Motor::Stop();
    delay(5); 
  break;

  case SlowOnTrack:
    Motion::Forwards(Speed-200);
    delay(5);
  break;

  case R_90:
    Motion::Rightwards_90(Speed);
    delay(5); 
  break;

  case L_90:
    Motion::Leftwards_90(Speed);
    delay(5);
  break;

  case R_135:
    Motion::Rightwards_135(Speed);
    delay(5);

  case L_135:
    Motion::Leftwards_135(Speed);
    delay(5);
  }
}
  
void LineTracking::stop(){
  Motor::Stop();
  Serial.println("222");
  delay(5); //You may change the delay duration 
};
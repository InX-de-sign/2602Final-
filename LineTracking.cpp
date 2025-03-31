#include "LineTracking.hpp"

void LineTracking::FollowingLine( uint8_t Case, uint16_t Speed ){
  switch (Case)
  {
  /*Change the Motion::ACTION for each case or Motor::Syop() for stop*/
  case OnTrack:
    Motion::Forwards(Speed);
    delay(10); //You may change the delay duration 
    //31/3changed: delay(1)-->delay(10)
  break;

  case IR_LOnTrack:
    Motion::Leftwards(Speed);
    delay(10); //You may change the delay duration 
  break;

  case IR_ROnTrack:
    Motion::Rightwards(Speed);
    delay(10); //You may change the delay duration 
  break;

  case AllOnTrack:
    Motor::Stop();
    delay(10); //You may change the delay duration 
  break;
  
  case IR_LandROnTrack:
    Motion::Forwards(Speed);
    delay(10); //You may change the delay duration 
  break;

  case OutOfTrack:
    Motion::Backwards(Speed);
    delay(10); //You may change the delay duration 

  break;
  }
};

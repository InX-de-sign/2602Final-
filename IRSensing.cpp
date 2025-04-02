#include "esp32-hal-gpio.h"
#include "IRSensing.hpp"

/*Initialize all the IR sensor Data Pins*/
void IR::Init(){
  pinMode(IR_L,INPUT);
  pinMode(IR_M,INPUT);
  pinMode(IR_R,INPUT);
};
/*For the Logic
  0: White 
  1: Black*/

bool IR::OnStartingLine(){
  if(digitalRead(IR_M) && (digitalRead(IR_L)) && (digitalRead(IR_R))){ //111 start
    return true; 
  }
  else{
    return false;
  }
}


uint8_t IR::Tracking(){
  //M_IR on Track
  if(digitalRead(IR_M) && !(digitalRead(IR_L)) && !(digitalRead(IR_R))) //! mean '0',white, 010
    return OnTrack;
  //R_IR on Track 
  if((!digitalRead(IR_M) && (!digitalRead(IR_L)) && (digitalRead(IR_R))) || (digitalRead(IR_M) && (!digitalRead(IR_L)) && (digitalRead(IR_R)))) //001 or 011
    return IR_ROnTrack;  
  //L_IR on Track 
  if(!digitalRead(IR_M) && (digitalRead(IR_L)) && !(digitalRead(IR_R)) || (digitalRead(IR_M) && (digitalRead(IR_L)) && !(digitalRead(IR_R)))) //100 or 110
    return IR_LOnTrack;
  //L_IR and R_IR are on Track
  if(!digitalRead(IR_M) && (digitalRead(IR_L)) && (digitalRead(IR_R)))// || (digitalRead(IR_M) && (digitalRead(IR_L)) && (digitalRead(IR_R)))) //101
    return IR_LandROnTrack;
  //All on Track
  if(digitalRead(IR_M) && (digitalRead(IR_L)) && (digitalRead(IR_R))) //111
    return AllOnTrack;
  

  return OutOfTrack; //000
};


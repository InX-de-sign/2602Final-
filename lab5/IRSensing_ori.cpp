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
  if(digitalRead(IR_M) && (digitalRead(IR_L)) && (digitalRead(IR_R))){
    return true; 
  }
  else{
    return false;
  }
}


uint8_t IR::Tracking(){ //!light 
  //M_IR on Track 010
  if(digitalRead(IR_M) && !(digitalRead(IR_L)) && !(digitalRead(IR_R)))
    return OnTrack;
    //return AllOnTrack;
  //R_IR on Track 001 & 011
  if((!digitalRead(IR_M) && (!digitalRead(IR_L)) && (digitalRead(IR_R))) || (digitalRead(IR_M) && (!digitalRead(IR_L)) && (digitalRead(IR_R))))
    return IR_ROnTrack;  
    //return AllOnTrack;
  //L_IR on Track 100 & 110
  if(!digitalRead(IR_M) && (digitalRead(IR_L)) && !(digitalRead(IR_R)) || (digitalRead(IR_M) && (digitalRead(IR_L)) && !(digitalRead(IR_R))))
    return IR_LOnTrack;
    //return AllOnTrack;
  //L_IR and R_IR are on Track 101 
  if(!digitalRead(IR_M) && (digitalRead(IR_L)) && (digitalRead(IR_R)))// || (digitalRead(IR_M) && (digitalRead(IR_L)) && (digitalRead(IR_R))))
    return IR_LandROnTrack;
    //return AllOnTrack;
  //All on Track 111
  if(digitalRead(IR_M) && (digitalRead(IR_L)) && (digitalRead(IR_R)))
    return AllOnTrack;
  
  //000
  return AllOnTrack; 
};

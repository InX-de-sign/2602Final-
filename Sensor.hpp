#ifndef Sensor_H_
#define Sensor_H_
#include "Pinout.hpp"
#include <Arduino.h>

#define OutOfTrack  0 
#define OnTrack     1
#define IR_ROnTrack 2
#define IR_LOnTrack 3 
#define IR_Finish   4
#define AllOnTrack  5
#define SlowOnTrack 6
#define R_90        7
#define L_90        8
#define R_135       9
#define L_135       10

extern  bool L;
extern  bool M;
extern  bool R;

// for test tasks
// #define default     0
// #define Task1       1
// #define Task2       2
// #define Task3_1     3
// #define Task3_2     4
// #define Task4_1     5
// #define Task4_2     6

/*define sound speed in m*/
#define SOUND_SPEED 340

namespace IR {
  void Init();
  uint8_t Tracking();
  uint8_t Task1();
  uint8_t Task2();
  uint8_t Task3();
  uint8_t Task4();
};

namespace Ultrasonic {
  void Init();
  float GetDistance(); //return distance in meter
}

#endif
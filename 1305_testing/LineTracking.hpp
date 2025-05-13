#ifndef LineTracking_H_
#define LineTracking_H_
#include "Pinout.hpp"
#include "Sensor.hpp"
#include <Arduino.h>

namespace LineTracking{
  void FollowingLine( uint8_t Case, uint16_t Speed );
  void stop();
}

#endif
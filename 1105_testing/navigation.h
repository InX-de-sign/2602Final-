#ifndef NAVIGATION_H
#define NAVIGATION_H

#include <Arduino.h>
#include "Sensor.hpp"

const uint8_t task3_node6 = 1;
const uint8_t task3_node8 = 2;

const uint8_t task4_node1 = 1; 
const uint8_t task4_node4 = 2;

namespace Navigation {
  struct TestCase {
    uint8_t main_case;      // 1-5
    uint8_t sub_case;       // For cases 3 & 4 (1-2)
    uint8_t sub_sub_case;   // For case 5 (1-30)
  };

  // Main navigation handler
  // void navigate(const TestCase& params);
  void handleTask1();
  void handleTask2();
  void handleTask3(uint8_t sub_case); 
  void handleTask4(uint8_t sub_case);
  void handleTask5(uint8_t sub_case);
};

#endif
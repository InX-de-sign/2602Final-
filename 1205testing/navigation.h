#ifndef NAVIGATION_H
#define NAVIGATION_H

#include <Arduino.h>
#include "Sensor.hpp"

#define MAX_PATH_LENGTH 8
#define MAX_PATHS 66

const uint8_t task3_node6 = 1;
const uint8_t task3_node8 = 2;

const uint8_t task4_node1 = 1; 
const uint8_t task4_node4 = 2;

struct NodeCondition {
  bool active;       
  const char* name;  
  void (*action)();  
};

struct Path {
    uint8_t start;
    uint8_t end;
    uint8_t nodes[MAX_PATH_LENGTH];
    uint8_t length;
    uint16_t cost;
};

extern NodeCondition ALL_NODE_CONDITIONS[54];

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
  bool getOptimalPath(uint8_t start, uint8_t end, Path& result);
};

#endif
#ifndef NAVIGATION_H
#define NAVIGATION_H

#include <Arduino.h>
#include "Sensor.hpp"

#define MAX_PATH_LENGTH 8
#define MAX_PATHS 66
#define TOTAL_NODES_CONDITIONS 54

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

extern NodeCondition ALL_NODE_CONDITIONS[TOTAL_NODES_CONDITIONS];

namespace Navigation {
  enum PathType {
    P1_4, P1_6, P1_7, P1_8, P1_9, P1_10, P1_11,
    P2_4, P2_5, P2_6, P2_7, P2_8, P2_10, P2_11,
    P3_5, P3_6, P3_7, P3_8, P3_9, P3_10, P3_11,
    P4_1, P4_2, P4_6, P4_8, P4_9, P4_10, P4_11,
    P5_2, P5_3, P5_6, P5_7, P5_8, P5_9, P5_11,
    P7_1, P7_2, P7_3, P7_5, P7_9, P7_10,
    P9_1, P9_3, P9_4, P9_5, P9_6, P9_7, P9_8,
    P10_1, P10_2, P10_3, P10_4, P10_6, P10_7, P10_8,
    P11_1, P11_2, P11_3, P11_4, P11_5, P11_6, P11_8
  };

  // struct TestCase {
  //   uint8_t main_case;      // 1-5
  //   uint8_t sub_case;       // For cases 3 & 4 (1-2)
  //   uint8_t sub_sub_case;   // For case 5 (1-30)
  // };

  // Main navigation handler
  // void navigate(const TestCase& params);
  void handleTask1();
  void handleTask2();
  void handleTask3(uint8_t sub_case); 
  void handleTask4(uint8_t sub_case);
  void handleTask5(uint8_t sub_case);
  Path* getOptimalPath(uint8_t start, uint8_t end);
  void navigatePath(const Path& path);
};

#endif
//
// Created by Mingfei Deng on 2020/7/1.
//

#ifndef LOCKER_LOCKERROBOTDIRECTOR_H
#define LOCKER_LOCKERROBOTDIRECTOR_H
#include "LockerRobotManager.h"
#include <iostream>

class LockerRobotDirector {
public:
  LockerRobotDirector(
      std::vector<LockerRobotManager> lockerRobotManagers);
  std::string Report();
private:
  std::vector<LockerRobotManager> locker_robot_managers;
};

#endif // LOCKER_LOCKERROBOTDIRECTOR_H

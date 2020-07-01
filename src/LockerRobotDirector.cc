//
// Created by Mingfei Deng on 2020/7/1.
//

#include "../include/LockerRobotDirector.h"

#include <utility>
LockerRobotDirector::LockerRobotDirector(
    std::vector<LockerRobotManager> lockerRobotManagers)
    : locker_robot_managers(std::move(lockerRobotManagers)) {}

std::string LockerRobotDirector::Report() {
  std::string report;
  for (auto one_manger : locker_robot_managers){
    report += one_manger.Report();
  }

  return report;
}

//
// Created by Mingfei Deng on 2020/6/22.
//

#ifndef LOCKER_LOCKERROBOTMANAGER_H
#define LOCKER_LOCKERROBOTMANAGER_H
#include "PrimaryLockerRobot.h"


class LockerRobotManager {
public:
  LockerRobotManager(const std::vector<Locker*>& lockers);
  SaveBagResult SaveBag(const Bag& bag);
  GetBagResult GetBag(const Ticket& ticket);
private:
  PrimaryLockerRobot internal_;

public:
  LockerRobotManager(std::vector<Robot *> managedRobot);
private:
  std::vector<Robot*> managed_robot;
};

#endif // LOCKER_LOCKERROBOTMANAGER_H

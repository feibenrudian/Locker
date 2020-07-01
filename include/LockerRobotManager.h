//
// Created by Mingfei Deng on 2020/6/22.
//

#ifndef LOCKER_LOCKERROBOTMANAGER_H
#define LOCKER_LOCKERROBOTMANAGER_H
#include "PrimaryLockerRobot.h"


class LockerRobotManager {
public:
  LockerRobotManager(const std::vector<Locker*>& lockers);
  LockerRobotManager(std::vector<Robot *> managedRobot);
  LockerRobotManager(const std::vector<Locker*>& lockers,
                     std::vector<Robot *>  managedRobot);
  SaveBagResult SaveBag(const Bag& bag);
  GetBagResult GetBag(const Ticket& ticket);
  std::string Report();

private:
  std::vector<Robot*> managed_robot;
  PrimaryLockerRobot internal_;
};

#endif // LOCKER_LOCKERROBOTMANAGER_H

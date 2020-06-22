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
private:
  PrimaryLockerRobot internal_;
};

#endif // LOCKER_LOCKERROBOTMANAGER_H

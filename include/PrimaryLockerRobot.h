//
// Created by Mingfei Deng on 2020/6/16.
//

#ifndef LOCKER_PRIMARYLOCKERROBOT_H
#define LOCKER_PRIMARYLOCKERROBOT_H

#include "Locker.h"
#include <vector>

class PrimaryLockerRobot {
public:
  virtual SaveBagResult SaveBag(const Bag& bag);
  std::vector<Locker*> manage_lockers;
  PrimaryLockerRobot(const std::vector<Locker *> &manageLockers);
  virtual GetBagResult GetBag(const Ticket& ticket);
};

#endif // LOCKER_PRIMARYLOCKERROBOT_H

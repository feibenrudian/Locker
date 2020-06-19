//
// Created by Mingfei Deng on 2020/6/16.
//

#ifndef LOCKER_PRIMARYLOCKERROBOT_H
#define LOCKER_PRIMARYLOCKERROBOT_H

#include "Locker.h"
#include "Robot.h"
#include <vector>

class PrimaryLockerRobot : public Robot {
public:
  PrimaryLockerRobot(const std::vector<Locker *> &manageLockers);
  SaveBagResult SaveBag(const Bag& bag);
};

#endif // LOCKER_PRIMARYLOCKERROBOT_H

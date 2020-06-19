//
// Created by Mingfei Deng on 2020/6/19.
//

#ifndef LOCKER_SMARTLOCKERROBOT_H
#define LOCKER_SMARTLOCKERROBOT_H
#include "Robot.h"

class SmartLockerRobot : public Robot {
public:
  SmartLockerRobot(const std::vector<Locker *> &manageLockers);
  SaveBagResult SaveBag(const Bag &bag) override;
};

#endif // LOCKER_SMARTLOCKERROBOT_H

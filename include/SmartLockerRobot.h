//
// Created by Mingfei Deng on 2020/6/19.
//

#ifndef LOCKER_SMARTLOCKERROBOT_H
#define LOCKER_SMARTLOCKERROBOT_H
#include "PrimaryLockerRobot.h"

class SmartLockerRobot : public PrimaryLockerRobot {
public:
  SmartLockerRobot(const std::vector<Locker *> &manageLockers);
  SaveBagResult SaveBag(const Bag &bag) override;
  GetBagResult GetBag(const Ticket &ticket) override;
};

#endif // LOCKER_SMARTLOCKERROBOT_H

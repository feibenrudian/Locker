//
// Created by Mingfei Deng on 2020/6/19.
//

#ifndef LOCKER_SMARTROBOT_H
#define LOCKER_SMARTROBOT_H
#include "Robot.h"

class SmartRobot : public Robot {
public:
  SmartRobot(const std::vector<Locker *> &manageLockers);
  SaveBagResult SaveBag(const Bag &bag) override;
  GetBagResult GetBag(const Ticket &ticket) override;
};

#endif // LOCKER_SMARTROBOT_H

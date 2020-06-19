//
// Created by Mingfei Deng on 2020/6/19.
//

#ifndef LOCKER_ROBOT_H
#define LOCKER_ROBOT_H

#include "Locker.h"
#include <vector>

class Robot {
public:
  Robot(std::vector<Locker *> manageLockers);
  virtual SaveBagResult SaveBag(const Bag& bag) = 0;
  GetBagResult GetBag(const Ticket& ticket);

  std::vector<Locker*> manage_lockers;
};

#endif // LOCKER_ROBOT_H

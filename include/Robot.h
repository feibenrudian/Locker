//
// Created by Mingfei Deng on 2020/6/16.
//

#ifndef LOCKER_ROBOT_H
#define LOCKER_ROBOT_H

#include "Locker.h"
#include <vector>

class Robot {
public:
  SaveBagResult SaveBag(Bag bag);
  std::vector<Locker*> manage_lockers;
  Robot(const std::vector<Locker *> &manageLockers);
};

#endif // LOCKER_ROBOT_H

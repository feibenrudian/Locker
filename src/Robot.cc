//
// Created by Mingfei Deng on 2020/6/16.
//

#include "../include/Robot.h"

SaveBagResult Robot::SaveBag(Bag bag) {
  for (auto one_locker : manage_lockers){
    if (0 != one_locker->remain){
      return  one_locker->SaveBag(bag);
    }
  }

  SaveBagResult ret;
  ret.err = 1;
  return ret;
}
Robot::Robot(const std::vector<Locker *> &manageLockers)
    : manage_lockers(manageLockers) {}

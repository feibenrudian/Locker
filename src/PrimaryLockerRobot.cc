//
// Created by Mingfei Deng on 2020/6/16.
//

#include "../include/PrimaryLockerRobot.h"

PrimaryLockerRobot::PrimaryLockerRobot(
    const std::vector<Locker *> &manageLockers)
    : Robot(manageLockers) {}

SaveBagResult PrimaryLockerRobot::SaveBag(const Bag &bag) {
  for (auto one_locker : manage_lockers) {
    if (0 != one_locker->remain) {
      return one_locker->SaveBag(bag);
    }
  }

  SaveBagResult ret;
  ret.err = save_bag_locker_full;
  return ret;
}

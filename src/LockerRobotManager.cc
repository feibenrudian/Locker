//
// Created by Mingfei Deng on 2020/6/22.
//

#include "../include/LockerRobotManager.h"
LockerRobotManager::LockerRobotManager(const std::vector<Locker*>& lockers)
    : internal_(lockers) {}

SaveBagResult LockerRobotManager::SaveBag(const Bag &bag) {
  return internal_.SaveBag(bag);
}

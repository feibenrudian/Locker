//
// Created by Mingfei Deng on 2020/6/22.
//

#include "../include/LockerRobotManager.h"

#include <utility>
LockerRobotManager::LockerRobotManager(const std::vector<Locker*>& lockers)
    : internal_(lockers) {}

LockerRobotManager::LockerRobotManager(std::vector<Robot *> managedRobot)
    : managed_robot(std::move(managedRobot)), internal_({}) {}

SaveBagResult LockerRobotManager::SaveBag(const Bag &bag) {
  if (!managed_robot.empty()){
    for (auto one_robot : managed_robot){
      SaveBagResult save_bag_result = one_robot->SaveBag(bag);
      if (save_bag_success == save_bag_result.err){
        return save_bag_result;
      }
    }
  }

  return internal_.SaveBag(bag);
}
GetBagResult LockerRobotManager::GetBag(const Ticket &ticket) {
  if (!managed_robot.empty()){
    for (auto one_robot : managed_robot){
      GetBagResult get_bag_result = one_robot->GetBag(ticket);
      if (get_bag_success == get_bag_result.err){
        return get_bag_result;
      }
    }
  }

  return internal_.GetBag(ticket);
}


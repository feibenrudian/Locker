//
// Created by Mingfei Deng on 2020/6/16.
//

#include "../include/Robot.h"

Robot::Robot(const std::vector<Locker *> &manageLockers)
    : manage_lockers(manageLockers) {}

SaveBagResult Robot::SaveBag(const Bag& bag) {
  for (auto one_locker : manage_lockers){
    if (0 != one_locker->remain){
      return  one_locker->SaveBag(bag);
    }
  }

  SaveBagResult ret;
  ret.err = save_bag_locker_full;
  return ret;
}

GetBagResult Robot::GetBag(const Ticket &ticket) {

  for (auto one_locker : manage_lockers){
    auto get_bag_result =  one_locker->GetBag(ticket);
    if (0 == get_bag_result.err){
      return get_bag_result;
    }
  }

  return GetBagResult{get_bag_illegal_ticket, Bag(0)};
}

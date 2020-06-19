//
// Created by Mingfei Deng on 2020/6/16.
//

#include "../include/PrimaryLockerRobot.h"

PrimaryLockerRobot::PrimaryLockerRobot(const std::vector<Locker *> &manageLockers)
    : manage_lockers(manageLockers) {}

SaveBagResult PrimaryLockerRobot::SaveBag(const Bag& bag) {
  for (auto one_locker : manage_lockers){
    if (0 != one_locker->remain){
      return  one_locker->SaveBag(bag);
    }
  }

  SaveBagResult ret;
  ret.err = save_bag_locker_full;
  return ret;
}

GetBagResult PrimaryLockerRobot::GetBag(const Ticket &ticket) {

  for (auto one_locker : manage_lockers){
    auto get_bag_result =  one_locker->GetBag(ticket);
    if (0 == get_bag_result.err){
      return get_bag_result;
    }
  }

  return GetBagResult{get_bag_illegal_ticket, Bag(0)};
}

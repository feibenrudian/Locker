//
// Created by Mingfei Deng on 2020/6/19.
//

#include "../include/Robot.h"

#include <utility>
Robot::Robot(std::vector<Locker *> manageLockers)
    : manage_lockers(std::move(manageLockers)) {}


GetBagResult Robot::GetBag(const Ticket &ticket) {

  for (auto one_locker : manage_lockers){
    auto get_bag_result =  one_locker->GetBag(ticket);
    if (0 == get_bag_result.err){
      return get_bag_result;
    }
  }

  return GetBagResult{get_bag_illegal_ticket, Bag(0)};
}
Robot::~Robot() {}

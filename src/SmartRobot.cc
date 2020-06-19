//
// Created by Mingfei Deng on 2020/6/19.
//

#include "../include/SmartRobot.h"
#include "../include/Locker.h"
#include "../include/Robot.h"
SaveBagResult SmartRobot::SaveBag(const Bag &bag) {
  Locker* save_locker;
  int remain = 0;

  for (auto& one_locker : manage_lockers){
    if (one_locker->remain > remain){
      save_locker = one_locker;
      remain = one_locker->remain;
    }
  }

  if (0 != remain){
    return save_locker->SaveBag(bag);
  }

  SaveBagResult ret;
  ret.err = save_bag_locker_full;

  return ret;
}
GetBagResult SmartRobot::GetBag(const Ticket &ticket) {

  return Robot::GetBag(ticket);
}
SmartRobot::SmartRobot(const std::vector<Locker *> &manageLockers)
    : Robot(manageLockers) {}

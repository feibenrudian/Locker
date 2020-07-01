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
ReportData Robot::Report() {
  int remain = 0;
  int amount = 0;

  for (auto one_locker : manage_lockers ){
    remain += one_locker->remain;
    amount += one_locker->amount;
  }

  std::string report = "R " + std::to_string(remain) + " " + std::to_string(amount) + "\n";

  for (auto one_locker : manage_lockers ){
    report += "\t" + one_locker->Report();
  }

  ReportData ret;
  ret.amount = amount;
  ret.remain = remain;
  ret.display_content = report;

  return ret;
}

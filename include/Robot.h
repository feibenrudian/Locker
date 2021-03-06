//
// Created by Mingfei Deng on 2020/6/19.
//

#ifndef LOCKER_ROBOT_H
#define LOCKER_ROBOT_H

#include "Locker.h"
#include <vector>
#include <iostream>

struct ReportData{
  int remain = 0;
  int amount = 0;
  std::string display_content;
};

class Robot {
public:
  Robot(std::vector<Locker *> manageLockers);
  virtual ~Robot();
  virtual SaveBagResult SaveBag(const Bag& bag) = 0;
  GetBagResult GetBag(const Ticket& ticket);
  ReportData Report(std::string report_head);

  std::vector<Locker*> manage_lockers;
};

#endif // LOCKER_ROBOT_H

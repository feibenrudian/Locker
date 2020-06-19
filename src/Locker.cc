//
// Created by Mingfei Deng. Ruolin Liang on 2020/6/16.
//

#include "../include/Locker.h"
#include <random>


Locker::Locker(int remain) : remain(remain) {}
SaveBagResult Locker::SaveBag(const Bag &save_bag) {
  SaveBagResult ret;

  if (0 == remain){
    ret.err = save_bag_locker_full;
    return ret;
  }

  ret.err = save_bag_success;
  ret.ticket.id = rand();
  content[ret.ticket.id] = save_bag;
  remain--;
  return ret;
}
GetBagResult Locker::GetBag(const Ticket &ticket) {

  if (content.count(ticket.id) != 0){
    GetBagResult result(get_bag_success, content[ticket.id]);
    content.erase(ticket.id);
    remain++;
    return result;
  }

  return GetBagResult{get_bag_illegal_ticket, Bag(0)};
}


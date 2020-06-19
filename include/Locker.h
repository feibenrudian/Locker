//
// Created by Mingfei Deng. Ruolin Liang on 2020/6/16.
//

#ifndef GILEROSS_LOCKER_H
#define GILEROSS_LOCKER_H
#include <map>

struct Bag {
  int id;//id is 0, means null bag
  Bag(int id) : id(id) {}
  Bag(){};
};

struct Ticket{
  int id = 0;
};

enum save_bag_result_err{
  save_bag_success = 0,
  save_bag_locker_full = 1
};

struct SaveBagResult{
  save_bag_result_err err;
  Ticket ticket;
};

enum get_bag_result_err{
  get_bag_success = 0,
  get_bag_illegal_ticket = 1
};

struct GetBagResult {
  GetBagResult(get_bag_result_err err, const Bag &bag) : err(err), bag(bag) {}
  get_bag_result_err err;
  Bag bag;
};

class Locker {
public:
  SaveBagResult SaveBag(const Bag& save_bag);
  GetBagResult GetBag(const Ticket& ticket);
  int remain = 0;
  Locker(int remain);

  std::map<int, Bag> content;
};

#endif // GILEROSS_LOCKER_H

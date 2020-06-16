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

struct SaveBagResult{
  int err; //0 success, 1 full err
  Ticket ticket;
};

struct GetBagResult {
  GetBagResult(int err, const Bag &bag) : err(err), bag(bag) {}
  int err; //0 success, 1 illegal ticket
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

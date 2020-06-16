//
// Created by Mingfei Deng. Ruolin Liang on 2020/6/16.
//

#ifndef GILEROSS_LOCKER_H
#define GILEROSS_LOCKER_H


struct Bag {
  int id;
};

struct Ticket{
  int id = 0;
};

struct SaveBagResult{
  int err; //0 success, 1 full err
  Ticket ticket;
};

class Locker {
public:
  SaveBagResult SaveBag(const Bag& save_bag);
  int remain = 0;
  Locker(int remain);
};

#endif // GILEROSS_LOCKER_H

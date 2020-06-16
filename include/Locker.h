//
// Created by Mingfei Deng. Ruolin Liang on 2020/6/16.
//

#ifndef GILEROSS_LOCKER_H
#define GILEROSS_LOCKER_H


struct Bag {
  int id;
};

struct Ticket{
  int id;
};


struct SaveBagResult{
  int err;
  Ticket ticket;
};

class Locker {
public:
  SaveBagResult SaveBag(const Bag& save_bag);
  int remain = 0;
  Locker(int remain);
};

#endif // GILEROSS_LOCKER_H

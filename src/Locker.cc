//
// Created by Mingfei Deng. Ruolin Liang on 2020/6/16.
//

#include "../include/Locker.h"
#include <cstdlib>


Locker::Locker(int remain) : remain(remain) {}
SaveBagResult Locker::SaveBag(const Bag &save_bag) {
  SaveBagResult ret;

  if (0 == remain){
    ret.err = 1;
    return ret;
  }


  ret.err = 0;
  ret.ticket.id = rand();
  remain--;
  return ret;
}

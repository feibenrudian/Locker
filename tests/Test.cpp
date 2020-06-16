#include <gtest/gtest.h>
#include "../include/Locker.h"

using namespace std;

TEST(locker, should_return_ticket_when_store_bag_given_locker_is_not_full) {
  Locker locker(20);
  Bag bag;

  SaveBagResult result = locker.SaveBag(bag);

  EXPECT_EQ(0, result.err);
  EXPECT_NE(0, result.ticket.id);
  EXPECT_EQ(19, locker.remain);
}




#include <gtest/gtest.h>
#include "../include/Locker.h"

using namespace std;

TEST(locker, should_return_ticket_when_store_bag_given_locker_is_not_full) {
  //given
  Locker locker(20);
  Bag bag;

  //when
  SaveBagResult result = locker.SaveBag(bag);

  //then
  EXPECT_EQ(0, result.err);
  EXPECT_NE(0, result.ticket.id);
  EXPECT_EQ(19, locker.remain);
}

TEST(locker, should_show_error_message_when_store_bag_given_locker_is_full){
  //given
  Locker locker(1);
  Bag bag;
  SaveBagResult temp_result = locker.SaveBag(bag);

  //when
  SaveBagResult result = locker.SaveBag(bag);

  //then
  EXPECT_EQ(1, result.err);
  EXPECT_EQ(0, result.ticket.id);
  EXPECT_EQ(0, locker.remain);
}


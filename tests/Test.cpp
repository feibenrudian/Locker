#include <gtest/gtest.h>
#include "../include/Locker.h"
#include "../include/Robot.h"

using namespace std;

TEST(locker, should_return_ticket_when_store_bag_given_locker_is_not_full) {
  //given
  Locker locker(20);
  Bag bag(666);

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
  Bag bag(666);
  SaveBagResult temp_result = locker.SaveBag(bag);

  //when
  SaveBagResult result = locker.SaveBag(bag);

  //then
  EXPECT_EQ(1, result.err);
  EXPECT_EQ(0, result.ticket.id);
  EXPECT_EQ(0, locker.remain);
}

TEST(locker, should_return_bag_when_get_bag_given_valid_ticket){
  //given
  Locker locker(20);
  Bag bag(666);
  SaveBagResult save_bag_result = locker.SaveBag(bag);

  //when
  GetBagResult result = locker.GetBag(save_bag_result.ticket);

  //then
  EXPECT_EQ(0, result.err);
  EXPECT_EQ(666, result.bag.id);
  EXPECT_EQ(20, locker.remain);
}

TEST(locker, should_show_invalid_ticket_message_when_get_bag_given_duplicated_ticket){
  //given
  Locker locker(20);
  Bag bag(666);
  SaveBagResult save_bag_result = locker.SaveBag(bag);
  (void)locker.GetBag(save_bag_result.ticket);

  //when
  GetBagResult result = locker.GetBag(save_bag_result.ticket);

  //then
  EXPECT_EQ(1, result.err);
  EXPECT_EQ(0, result.bag.id);
  EXPECT_EQ(20, locker.remain);
}

TEST(locker, should_show_invalid_ticket_message_when_get_bag_given_fake_ticket){
  //given
  Locker locker(20);
  Bag bag(666);
  (void)locker.SaveBag(bag);
  Ticket fake_ticket;

  //when
  GetBagResult result = locker.GetBag(fake_ticket);

  //then
  EXPECT_EQ(1, result.err);
  EXPECT_EQ(0, result.bag.id);
  EXPECT_EQ(19, locker.remain);
}

TEST(robot, should_return_ticket_when_store_bag_given_both_lockers_are_available){
  //given
  Locker locker1(10);
  Locker locker2(19);
  std::vector<Locker*> robot_manage_lockers;
  robot_manage_lockers.push_back(&locker1);
  robot_manage_lockers.push_back(&locker2);
  Robot robot(robot_manage_lockers);
  Bag bag(666);

  //when
  SaveBagResult result = robot.SaveBag(bag);

  //then
  EXPECT_EQ(0, result.err);
  EXPECT_NE(0, result.ticket.id);
  EXPECT_EQ(9, locker1.remain);
  EXPECT_EQ(19, locker2.remain);
}

TEST(robot, should_return_ticket_when_store_bag_given_first_full_and_second_available){
  //given
  Locker locker1(1);
  Locker locker2(19);
  std::vector<Locker*> robot_manage_lockers;
  robot_manage_lockers.push_back(&locker1);
  robot_manage_lockers.push_back(&locker2);
  Robot robot(robot_manage_lockers);
  Bag bag1(666);
  (void)robot.SaveBag(bag1);
  Bag bag2(6666);

  //when
  SaveBagResult result = robot.SaveBag(bag2);

  //then
  EXPECT_EQ(0, result.err);
  EXPECT_NE(0, result.ticket.id);
  EXPECT_EQ(0, locker1.remain);
  EXPECT_EQ(18, locker2.remain);
}

TEST(robot, should_show_store_error_when_store_bag_given_both_lockers_are_full){
  //given
  Locker locker1(1);
  Locker locker2(1);
  std::vector<Locker*> robot_manage_lockers;
  robot_manage_lockers.push_back(&locker1);
  robot_manage_lockers.push_back(&locker2);
  Robot robot(robot_manage_lockers);
  Bag bag1(666);
  (void)robot.SaveBag(bag1);
  Bag bag2(6666);
  (void)robot.SaveBag(bag2);
  Bag bag3(66666);

  //when
  SaveBagResult result = robot.SaveBag(bag3);

  //then
  EXPECT_EQ(1, result.err);
  EXPECT_EQ(0, result.ticket.id);
  EXPECT_EQ(0, locker1.remain);
  EXPECT_EQ(0, locker2.remain);
}

TEST(robot, should_return_bag_when_get_bag_given_valid_ticket){
  //given
  Locker locker1(10);
  Locker locker2(19);
  std::vector<Locker*> robot_manage_lockers;
  robot_manage_lockers.push_back(&locker1);
  robot_manage_lockers.push_back(&locker2);
  Robot robot(robot_manage_lockers);
  Bag bag(666);
  SaveBagResult save_bag_result = robot.SaveBag(bag);

  //when
  GetBagResult result = robot.GetBag(save_bag_result.ticket);

  //then
  EXPECT_EQ(0, result.err);
  EXPECT_EQ(666, result.bag.id);
  EXPECT_EQ(10, locker1.remain);
  EXPECT_EQ(19, locker2.remain);
}


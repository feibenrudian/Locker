#include "../include/Locker.h"
#include "../include/LockerRobotManager.h"
#include "../include/PrimaryLockerRobot.h"
#include "../include/SmartLockerRobot.h"
#include <gtest/gtest.h>

using namespace std;

TEST(locker, should_return_ticket_when_store_bag_given_locker_is_not_full) {
  // given
  Locker locker(20);
  Bag bag(666);

  // when
  SaveBagResult result = locker.SaveBag(bag);

  // then
  EXPECT_EQ(0, result.err);
  EXPECT_NE(0, result.ticket.id);
  EXPECT_EQ(19, locker.remain);
}

TEST(locker, should_show_error_message_when_store_bag_given_locker_is_full) {
  // given
  Locker locker(1);
  Bag bag(666);
  SaveBagResult temp_result = locker.SaveBag(bag);

  // when
  SaveBagResult result = locker.SaveBag(bag);

  // then
  EXPECT_EQ(1, result.err);
  EXPECT_EQ(0, result.ticket.id);
  EXPECT_EQ(0, locker.remain);
}

TEST(locker, should_return_bag_when_get_bag_given_valid_ticket) {
  // given
  Locker locker(20);
  Bag bag(666);
  SaveBagResult save_bag_result = locker.SaveBag(bag);

  // when
  GetBagResult result = locker.GetBag(save_bag_result.ticket);

  // then
  EXPECT_EQ(0, result.err);
  EXPECT_EQ(666, result.bag.id);
  EXPECT_EQ(20, locker.remain);
}

TEST(locker,
     should_show_invalid_ticket_message_when_get_bag_given_duplicated_ticket) {
  // given
  Locker locker(20);
  Bag bag(666);
  SaveBagResult save_bag_result = locker.SaveBag(bag);
  (void)locker.GetBag(save_bag_result.ticket);

  // when
  GetBagResult result = locker.GetBag(save_bag_result.ticket);

  // then
  EXPECT_EQ(1, result.err);
  EXPECT_EQ(0, result.bag.id);
  EXPECT_EQ(20, locker.remain);
}

TEST(locker,
     should_show_invalid_ticket_message_when_get_bag_given_fake_ticket) {
  // given
  Locker locker(20);
  Bag bag(666);
  (void)locker.SaveBag(bag);
  Ticket fake_ticket;

  // when
  GetBagResult result = locker.GetBag(fake_ticket);

  // then
  EXPECT_EQ(1, result.err);
  EXPECT_EQ(0, result.bag.id);
  EXPECT_EQ(19, locker.remain);
}

TEST(primary_locker_robot,
     should_return_ticket_when_store_bag_given_both_lockers_are_available) {
  // given
  Locker locker1(10);
  Locker locker2(19);
  std::vector<Locker *> robot_manage_lockers;
  robot_manage_lockers.push_back(&locker1);
  robot_manage_lockers.push_back(&locker2);
  PrimaryLockerRobot primary_locker_robot(robot_manage_lockers);
  Bag bag(666);

  // when
  SaveBagResult result = primary_locker_robot.SaveBag(bag);

  // then
  EXPECT_EQ(0, result.err);
  EXPECT_NE(0, result.ticket.id);
  EXPECT_EQ(9, locker1.remain);
  EXPECT_EQ(19, locker2.remain);
}

TEST(
    primary_locker_robot,
    should_return_ticket_when_store_bag_given_first_full_and_second_available) {
  // given
  Locker locker1(1);
  Locker locker2(19);
  std::vector<Locker *> robot_manage_lockers;
  robot_manage_lockers.push_back(&locker1);
  robot_manage_lockers.push_back(&locker2);
  PrimaryLockerRobot primary_locker_robot(robot_manage_lockers);
  Bag bag1(666);
  (void)primary_locker_robot.SaveBag(bag1);
  Bag bag2(6666);

  // when
  SaveBagResult result = primary_locker_robot.SaveBag(bag2);

  // then
  EXPECT_EQ(0, result.err);
  EXPECT_NE(0, result.ticket.id);
  EXPECT_EQ(0, locker1.remain);
  EXPECT_EQ(18, locker2.remain);
}

TEST(primary_locker_robot,
     should_show_store_error_when_store_bag_given_both_lockers_are_full) {
  // given
  Locker locker1(1);
  Locker locker2(1);
  std::vector<Locker *> robot_manage_lockers;
  robot_manage_lockers.push_back(&locker1);
  robot_manage_lockers.push_back(&locker2);
  PrimaryLockerRobot primary_locker_robot(robot_manage_lockers);
  Bag bag1(666);
  (void)primary_locker_robot.SaveBag(bag1);
  Bag bag2(6666);
  (void)primary_locker_robot.SaveBag(bag2);
  Bag bag3(66666);

  // when
  SaveBagResult result = primary_locker_robot.SaveBag(bag3);

  // then
  EXPECT_EQ(1, result.err);
  EXPECT_EQ(0, result.ticket.id);
  EXPECT_EQ(0, locker1.remain);
  EXPECT_EQ(0, locker2.remain);
}

TEST(primary_locker_robot, should_return_bag_when_get_bag_given_valid_ticket) {
  // given
  Locker locker1(10);
  Locker locker2(19);
  std::vector<Locker *> robot_manage_lockers;
  robot_manage_lockers.push_back(&locker1);
  robot_manage_lockers.push_back(&locker2);
  PrimaryLockerRobot primary_locker_robot(robot_manage_lockers);
  Bag bag(666);
  SaveBagResult save_bag_result = primary_locker_robot.SaveBag(bag);

  // when
  GetBagResult result = primary_locker_robot.GetBag(save_bag_result.ticket);

  // then
  EXPECT_EQ(0, result.err);
  EXPECT_EQ(666, result.bag.id);
  EXPECT_EQ(10, locker1.remain);
  EXPECT_EQ(19, locker2.remain);
}

TEST(primary_locker_robot,
     should_show_get_bag_error_when_get_bag_given_illegal_ticket) {
  // given
  Locker locker1(10);
  Locker locker2(19);
  std::vector<Locker *> robot_manage_lockers;
  robot_manage_lockers.push_back(&locker1);
  robot_manage_lockers.push_back(&locker2);
  PrimaryLockerRobot primary_locker_robot(robot_manage_lockers);
  Bag bag(666);
  (void)primary_locker_robot.SaveBag(bag);

  // when
  Ticket ticket;
  GetBagResult result = primary_locker_robot.GetBag(ticket);

  // then
  EXPECT_EQ(1, result.err);
  EXPECT_EQ(0, result.bag.id);
  EXPECT_EQ(9, locker1.remain);
  EXPECT_EQ(19, locker2.remain);
}

TEST(
    smart_locker_robot,
    should_store_bag_to_first_locker_when_save_bag_given_first_greater_than_second) {
  Locker locker1(10);
  Locker locker2(8);
  std::vector<Locker *> robot_manage_lockers;
  robot_manage_lockers.push_back(&locker1);
  robot_manage_lockers.push_back(&locker2);
  SmartLockerRobot smart_locker_robot(robot_manage_lockers);

  Bag bag(666);
  SaveBagResult result = smart_locker_robot.SaveBag(bag);

  EXPECT_EQ(save_bag_success, result.err);
  EXPECT_EQ(9, locker1.remain);
  EXPECT_EQ(8, locker2.remain);
}

TEST(
    smart_locker_robot,
    should_store_bag_to_second_locker_when_save_bag_given_second_greater_than_first) {
  Locker locker1(8);
  Locker locker2(10);
  std::vector<Locker *> robot_manage_lockers;
  robot_manage_lockers.push_back(&locker1);
  robot_manage_lockers.push_back(&locker2);
  SmartLockerRobot smart_locker_robot(robot_manage_lockers);

  Bag bag(666);
  SaveBagResult result = smart_locker_robot.SaveBag(bag);

  EXPECT_EQ(save_bag_success, result.err);
  EXPECT_EQ(8, locker1.remain);
  EXPECT_EQ(9, locker2.remain);
}

TEST(smart_locker_robot,
     should_store_bag_to_first_locker_when_save_bag_given_both_are_equal) {
  Locker locker1(10);
  Locker locker2(10);
  std::vector<Locker *> robot_manage_lockers;
  robot_manage_lockers.push_back(&locker1);
  robot_manage_lockers.push_back(&locker2);
  SmartLockerRobot smart_locker_robot(robot_manage_lockers);

  Bag bag(666);
  SaveBagResult result = smart_locker_robot.SaveBag(bag);

  EXPECT_EQ(save_bag_success, result.err);
  EXPECT_EQ(9, locker1.remain);
  EXPECT_EQ(10, locker2.remain);
}

TEST(smart_locker_robot,
     should_show_invalid_message_when_save_bag_given_both_are_full) {
  Locker locker1(1);
  Locker locker2(1);
  std::vector<Locker *> robot_manage_lockers;
  robot_manage_lockers.push_back(&locker1);
  robot_manage_lockers.push_back(&locker2);
  SmartLockerRobot smart_locker_robot(robot_manage_lockers);
  Bag bag1(666);
  (void)smart_locker_robot.SaveBag(bag1);
  Bag bag2(6666);
  (void)smart_locker_robot.SaveBag(bag2);

  Bag bag3(66);
  SaveBagResult result = smart_locker_robot.SaveBag(bag3);

  EXPECT_EQ(save_bag_locker_full, result.err);
  EXPECT_EQ(0, locker1.remain);
  EXPECT_EQ(0, locker2.remain);
}

TEST(smart_locker_robot,
     should_return_bag_when_smart_robot_get_bag_given_valid_ticket) {
  Locker locker1(8);
  Locker locker2(10);
  std::vector<Locker *> robot_manage_lockers;
  robot_manage_lockers.push_back(&locker1);
  robot_manage_lockers.push_back(&locker2);
  SmartLockerRobot smart_locker_robot(robot_manage_lockers);
  Bag bag(666);
  SaveBagResult save_bag_result = smart_locker_robot.SaveBag(bag);

  GetBagResult result = smart_locker_robot.GetBag(save_bag_result.ticket);

  EXPECT_EQ(get_bag_success, result.err);
  EXPECT_EQ(8, locker1.remain);
  EXPECT_EQ(10, locker2.remain);
  EXPECT_EQ(666, result.bag.id);
}

TEST(smart_locker_robot,
     should_show_get_bag_error_when_smart_robot_get_bag_given_illegal_ticket) {
  Locker locker1(8);
  Locker locker2(10);
  std::vector<Locker *> robot_manage_lockers;
  robot_manage_lockers.push_back(&locker1);
  robot_manage_lockers.push_back(&locker2);
  SmartLockerRobot smart_locker_robot(robot_manage_lockers);
  Bag bag(666);
  SaveBagResult save_bag_result = smart_locker_robot.SaveBag(bag);

  Ticket ticket;
  GetBagResult result = smart_locker_robot.GetBag(ticket);

  EXPECT_EQ(get_bag_illegal_ticket, result.err);
  EXPECT_EQ(8, locker1.remain);
  EXPECT_EQ(9, locker2.remain);
}

TEST(
    smart_locker_robot,
    should_return_bag_when_primary_robot_get_bag_given_ticket_from_smart_robot) {
  Locker locker1(8);
  Locker locker2(10);
  std::vector<Locker *> robot_manage_lockers;
  robot_manage_lockers.push_back(&locker1);
  robot_manage_lockers.push_back(&locker2);
  SmartLockerRobot smart_locker_robot(robot_manage_lockers);
  PrimaryLockerRobot primary_locker_robot(robot_manage_lockers);
  Bag bag(666);
  SaveBagResult save_bag_result = smart_locker_robot.SaveBag(bag);

  GetBagResult result = primary_locker_robot.GetBag(save_bag_result.ticket);

  EXPECT_EQ(get_bag_success, result.err);
  EXPECT_EQ(8, locker1.remain);
  EXPECT_EQ(10, locker2.remain);
  EXPECT_EQ(666, result.bag.id);
}

TEST(
    smart_locker_robot,
    should_rerurn_bag_when_smart_robot_get_bag_given_ticket_from_primary_robot) {
  Locker locker1(8);
  Locker locker2(10);
  std::vector<Locker *> robot_manage_lockers;
  robot_manage_lockers.push_back(&locker1);
  robot_manage_lockers.push_back(&locker2);
  SmartLockerRobot smart_locker_robot(robot_manage_lockers);
  PrimaryLockerRobot primary_locker_robot(robot_manage_lockers);
  Bag bag(666);
  SaveBagResult save_bag_result = primary_locker_robot.SaveBag(bag);

  GetBagResult result = smart_locker_robot.GetBag(save_bag_result.ticket);

  EXPECT_EQ(get_bag_success, result.err);
  EXPECT_EQ(8, locker1.remain);
  EXPECT_EQ(10, locker2.remain);
  EXPECT_EQ(666, result.bag.id);
}

std::vector<Locker *> InitTwoLockers(int first_remain, int second_remain) {
  auto *locker1 = new Locker(first_remain);
  auto *locker2 = new Locker(second_remain);
  std::vector<Locker *> lockers;
  lockers.push_back(locker1);
  lockers.push_back(locker2);

  return lockers;
}

void DeleteLockers(std::vector<Locker *> lockers) {
  for (auto one_locker : lockers) {
    delete one_locker;
  }
}

bool CheckBagInLocker(int bag_id, const Locker *lockers) {
  for (auto one_locker_item : lockers->content) {
    if (bag_id == one_locker_item.second.id) {
      return true;
    }
  }

  return false;
}

TEST(
    locker_robot_manager,
    should_store_bag_to_first_locker_when_save_bag_given_manager_only_has_lockers_and_both_are_available) {
  int bag_id = 666;
  auto lockers = InitTwoLockers(8, 10);
  LockerRobotManager locker_robot_manager(lockers);
  Bag bag(bag_id);

  SaveBagResult result = locker_robot_manager.SaveBag(bag);

  EXPECT_EQ(save_bag_success, result.err);
  auto bag_in_lockers = CheckBagInLocker(bag_id, lockers[0]);
  EXPECT_EQ(true, bag_in_lockers);

  DeleteLockers(lockers);
}

TEST(
    locker_robot_manager,
    should_store_bag_to_second_locker_when_save_bag_given_manager_only_has_lockers_and_first_is_full) {
  int bag_id1 = 666;
  int bag_id2 = 6666;
  auto lockers = InitTwoLockers(1, 10);
  LockerRobotManager locker_robot_manager(lockers);
  Bag bag1(bag_id1);
  Bag bag2(bag_id2);
  (void)locker_robot_manager.SaveBag(bag1);

  SaveBagResult result = locker_robot_manager.SaveBag(bag2);

  EXPECT_EQ(save_bag_success, result.err);
  auto bag_in_lockers = CheckBagInLocker(6666, lockers[1]);
  EXPECT_EQ(true, bag_in_lockers);

  DeleteLockers(lockers);
}

TEST(
    locker_robot_manager,
    should_show_error_when_save_bag_given_manager_only_has_lockers_and_both_are_full) {
  int bag_id1 = 666;
  int bag_id2 = 6666;
  int bag_id3 = 6669;
  auto lockers = InitTwoLockers(1, 1);
  LockerRobotManager locker_robot_manager(lockers);
  Bag bag1(bag_id1);
  Bag bag2(bag_id2);
  Bag bag3(bag_id3);
  (void)locker_robot_manager.SaveBag(bag1);
  (void)locker_robot_manager.SaveBag(bag2);

  SaveBagResult result = locker_robot_manager.SaveBag(bag3);

  EXPECT_EQ(save_bag_locker_full, result.err);

  DeleteLockers(lockers);
}

TEST(locker_robot_manager,
     should_return_bag_when_manager_get_bag_given_valid_ticket) {
  int bag_id = 666;
  auto lockers = InitTwoLockers(8, 10);
  LockerRobotManager locker_robot_manager(lockers);
  Bag bag(bag_id);
  SaveBagResult save_bag_result = locker_robot_manager.SaveBag(bag);

  GetBagResult result = locker_robot_manager.GetBag(save_bag_result.ticket);

  EXPECT_EQ(get_bag_success, result.err);
  EXPECT_EQ(666, result.bag.id);

  DeleteLockers(lockers);
}

TEST(locker_robot_manager,
     should_show_error_when_manager_get_bag_given_invalid_ticket) {

  auto lockers = InitTwoLockers(8, 10);
  LockerRobotManager locker_robot_manager(lockers);

  Ticket invalid_ticket;
  GetBagResult result = locker_robot_manager.GetBag(invalid_ticket);

  EXPECT_EQ(get_bag_illegal_ticket, result.err);

  DeleteLockers(lockers);
}

std::vector<Robot *>
InitTwoRobotBathHasOneLocker(int first_robot_locker_remain,
                             int second_robot_locker_remain) {
  auto locker1 = new Locker(first_robot_locker_remain);
  auto primary_locker_robot = new PrimaryLockerRobot({locker1});

  auto locker2 = new Locker(second_robot_locker_remain);
  auto smart_locker_robot = new SmartLockerRobot({locker2});

  return std::vector<Robot *>{primary_locker_robot, smart_locker_robot};
}

void DeleteRobots(std::vector<Robot *> robots){
  for (auto one_robot : robots){
    for (auto one_locker : one_robot->manage_lockers){
      delete one_locker;
    }

    delete one_robot;
  }
}


TEST(
    locker_robot_manager,
    should_store_bag_to_first_robot_locker_when_save_bag_given_manager_only_has_robots_and_both_are_available) {
  int bag_id = 666;
  auto Robots = InitTwoRobotBathHasOneLocker(8, 10);

  LockerRobotManager locker_robot_manager(Robots);
  Bag bag(bag_id);

  SaveBagResult result = locker_robot_manager.SaveBag(bag);

  EXPECT_EQ(save_bag_success, result.err);
  auto bag_in_lockers = CheckBagInLocker(666, Robots[0]->manage_lockers[0]);
  EXPECT_EQ(true, bag_in_lockers);

  DeleteRobots(Robots);
}

TEST(
    locker_robot_manager,
    should_store_bag_to_second_robot_locker_when_save_bag_given_manager_only_has_robots_and_first_robot_locker_is_full) {
  int bag_id1 = 666;
  int bag_id2 = 6666;
  auto Robots = InitTwoRobotBathHasOneLocker(1, 10);
  LockerRobotManager locker_robot_manager(Robots);
  Bag bag1(bag_id1);
  Bag bag2(bag_id2);
  (void)locker_robot_manager.SaveBag(bag1);

  SaveBagResult result = locker_robot_manager.SaveBag(bag2);

  EXPECT_EQ(save_bag_success, result.err);
  auto bag_in_lockers = CheckBagInLocker(6666, Robots[1]->manage_lockers[0]);
  EXPECT_EQ(true, bag_in_lockers);

  DeleteRobots(Robots);
}

TEST(
    locker_robot_manager,
    should_show_error_when_save_bag_given_manager_only_has_robots_and_both_are_full) {
  int bag_id1 = 666;
  int bag_id2 = 6666;
  int bag_id3 = 6669;
  auto Robots = InitTwoRobotBathHasOneLocker(1, 1);
  LockerRobotManager locker_robot_manager(Robots);
  Bag bag1(bag_id1);
  Bag bag2(bag_id2);
  Bag bag3(bag_id3);
  (void)locker_robot_manager.SaveBag(bag1);
  (void)locker_robot_manager.SaveBag(bag2);

  SaveBagResult result = locker_robot_manager.SaveBag(bag3);

  EXPECT_EQ(save_bag_locker_full, result.err);

  DeleteRobots(Robots);
}

TEST(
    locker_robot_manager,
    should_return_bag_when_manager_get_bag_given_valid_ticket_and_manager_only_has_two_robots) {
  int bag_id = 666;
  auto Robots = InitTwoRobotBathHasOneLocker(8, 10);
  LockerRobotManager locker_robot_manager(Robots);
  Bag bag(bag_id);
  SaveBagResult save_bag_result = locker_robot_manager.SaveBag(bag);

  GetBagResult result = locker_robot_manager.GetBag(save_bag_result.ticket);

  EXPECT_EQ(get_bag_success, result.err);
  EXPECT_EQ(666, result.bag.id);

  DeleteRobots(Robots);
}

TEST(
    locker_robot_manager,
    should_show_error_when_manager_get_bag_given_invalid_ticket_and_manager_only_has_two_robots) {
  int bag_id = 666;
  auto Robots = InitTwoRobotBathHasOneLocker(8, 10);
  LockerRobotManager locker_robot_manager(Robots);
  Bag bag(bag_id);
  (void) locker_robot_manager.SaveBag(bag);

  Ticket ticket;
  GetBagResult result = locker_robot_manager.GetBag(ticket);

  EXPECT_EQ(get_bag_illegal_ticket, result.err);

  DeleteRobots(Robots);
}

struct InitComplexRobotManagerResult{
  LockerRobotManager robot_manager;
  Robot* robot;
  Locker* one_locker;
  InitComplexRobotManagerResult(const LockerRobotManager &robotManager,
                                Robot *robot, Locker *oneLocker)
      : robot_manager(robotManager), robot(robot), one_locker(oneLocker) {}
};

InitComplexRobotManagerResult InitLockerRobotManagerWithOneRobotAndOneLocker(int first_robot_locker_remain,
                                                                  int second_locker_remain){
  auto locker1 = new Locker(second_locker_remain);
  Robot* robot = new PrimaryLockerRobot({new Locker(first_robot_locker_remain)});


  return InitComplexRobotManagerResult(LockerRobotManager({locker1}, {robot}), robot, locker1);
}


TEST(
    locker_robot_manager,
    should_store_bag_to_robot_locker_when_save_bag_given_manager_has_robot_and_locker_and_both_are_available) {
  int bag_id = 666;
  InitComplexRobotManagerResult locker_robot_manager_data = InitLockerRobotManagerWithOneRobotAndOneLocker(8, 10);
  Bag bag(bag_id);

  SaveBagResult result = locker_robot_manager_data.robot_manager.SaveBag(bag);


  EXPECT_EQ(save_bag_success, result.err);

  auto bag_in_lockers = CheckBagInLocker(666, locker_robot_manager_data.robot->manage_lockers[0]);
  EXPECT_EQ(true, bag_in_lockers);
}

TEST(
    locker_robot_manager,
    should_store_bag_to_locker_when_save_bag_given_manager_has_robot_and_locker_and_robot_locker_is_full) {
  int bag_id1 = 666;
  int bag_id2 = 6666;
  InitComplexRobotManagerResult locker_robot_manager_data = InitLockerRobotManagerWithOneRobotAndOneLocker(1, 10);
  Bag bag1(bag_id1);
  Bag bag2(bag_id2);
  (void)locker_robot_manager_data.robot_manager.SaveBag(bag1);


  SaveBagResult result = locker_robot_manager_data.robot_manager.SaveBag(bag2);

  EXPECT_EQ(save_bag_success, result.err);
  auto bag_in_lockers = CheckBagInLocker(6666, locker_robot_manager_data.one_locker);
  EXPECT_EQ(true, bag_in_lockers);
}


TEST(
    locker_robot_manager,
    should_show_error_when_save_bag_given_manager_has_robot_and_locker_and_both_are_full) {
  int bag_id1 = 666;
  int bag_id2 = 6666;
  int bag_id3 = 6669;
  InitComplexRobotManagerResult locker_robot_manager_data = InitLockerRobotManagerWithOneRobotAndOneLocker(1, 1);
  Bag bag1(bag_id1);
  Bag bag2(bag_id2);
  Bag bag3(bag_id3);
  (void)locker_robot_manager_data.robot_manager.SaveBag(bag1);
  (void)locker_robot_manager_data.robot_manager.SaveBag(bag2);

  SaveBagResult result = locker_robot_manager_data.robot_manager.SaveBag(bag3);

  EXPECT_EQ(save_bag_locker_full, result.err);
}

TEST(
    locker_robot_manager,
    should_return_bag_when_manager_get_bag_given_valid_ticket_and_manager_has_robot_and_locker) {
  int bag_id = 666;
  InitComplexRobotManagerResult locker_robot_manager_data = InitLockerRobotManagerWithOneRobotAndOneLocker(8, 10);
  Bag bag(bag_id);
  SaveBagResult save_bag_result = locker_robot_manager_data.robot_manager.SaveBag(bag);

  GetBagResult result = locker_robot_manager_data.robot_manager.GetBag(save_bag_result.ticket);


  EXPECT_EQ(get_bag_success, result.err);
  EXPECT_EQ(bag_id, result.bag.id);
}


ADD_SUBDIRECTORY(googletest EXCLUDE_FROM_ALL)
AUX_SOURCE_DIRECTORY(. SOURCE)
AUX_SOURCE_DIRECTORY(../src SOURCE)
ADD_EXECUTABLE(TempTest ${SOURCE} ../src/Locker.cc ../src/Robot.cc ../src/SmartRobot.cc ../src/SmartRobot.h)

TARGET_LINK_LIBRARIES(TempTest  gtest_main gmock_main)

ADD_TEST(NAME TempTest COMMAND TempTest)


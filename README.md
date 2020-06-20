# Locker
A practice for TDD   
***   
### Tasking - Locker
**Given** locker 有可用容量  **When** locker 存包  **Then** 存包成功，返回票据   

**Given** locker 已经存满  **When** 存包  **Then** 存包失败，提示储物柜已满  

**Given** 一张有效票据  **When** locker 取包  **Then** 取包成功  

**Given** 一张伪造票据  **When** locker 取包  **Then** 取包失败，提示非法票据

**Given** 一张重复使用的票据  **When** locker 取包  **Then** 取包失败，提示非法票据

***  
### Tasking - PrimaryLockerRobot  
**Given** 两个 locker，都有空间 **When** 机器人存包  **Then** 包成功存入第一个 locker，返回票

**Given** 两个 locker，第一个已满，第二个未满  **When** 机器人存包   **Then** 包成功存入第二个 locker，返回票

**Given** 两个 locker，都存满了  **When** 机器人存包  **Then** 存包失败

**Given** 一张有效票据  **When** 机器人取包  **Then** 取包成功

**Given** 一张无效票据  **When** 机器人取包  **Then** 取包失败

***
### Tasking - SmartLockerRobot
**Given** 两个 locker，第一个剩余容量大于第二个  **When** SmartLockerRobot 存包  **Then** 包存入第一个 locker，返回票  

**Given** 两个 locker，第二个剩余容量大于第一个  **When** SmartLockerRobot 存包  **Then** 包存入第二个 locker，返回票  

**Given** 两个 locker，剩余容量相等 **When** SmartLockerRobot 存包  **Then** 包存入第一个 locker，返回票  

**Given** 两个 locker，都存满了  **When** SmartLockerRobot 存包  **Then** 存包失败  

**Given** 一张有效票据  **When** SmartLockerRobot 取包  **Then** 取包成功  

**Given** 一张无效票据  **When** SmartLockerRobot 取包  **Then** 取包失败  

**Given** PrimaryLockerRobot 和 SmartLockerRobot 同时管理两个 Locker，提供一张 SmartLockerRobot 存包返回的票  **When** PrimaryLockerRobot 取包  **Then** 取包成功  

**Given** PrimaryLockerRobot 和 SmartLockerRobot 同时管理两个 Locker，提供一张 PrimaryLockerRobot 存包返回的票  **When** SmartLockerRobot 取包  **Then** 取包成功


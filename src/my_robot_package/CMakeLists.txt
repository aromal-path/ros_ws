cmake_minimum_required(VERSION 3.14)
project(my_robot_package)

## Specify C++ standard (compatible with Ubuntu 20.04)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

## Find catkin macros and libraries
find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  message_generation
)

## Declare service files
add_service_files(
  FILES
  AddTwoInts.srv
)

## Generate messages and services
generate_messages(
  DEPENDENCIES
  std_msgs
)

## Define catkin package
catkin_package(
  CATKIN_DEPENDS roscpp rospy std_msgs message_runtime
)

## Include directories
include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

## Declare C++ executables
add_executable(test_params src/test_params.cpp)
add_executable(add_two_ints_server src/add_two_ints_server.cpp)
add_executable(add_two_ints_client src/add_two_ints_client.cpp)

## Add dependencies
add_dependencies(test_params ${catkin_EXPORTED_TARGETS})
add_dependencies(add_two_ints_server ${catkin_EXPORTED_TARGETS})
add_dependencies(add_two_ints_client ${catkin_EXPORTED_TARGETS})

## Link executables with catkin libraries
target_link_libraries(test_params ${catkin_LIBRARIES})
target_link_libraries(add_two_ints_server ${catkin_LIBRARIES})
target_link_libraries(add_two_ints_client ${catkin_LIBRARIES})

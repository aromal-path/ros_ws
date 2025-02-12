#include <ros/init.h>
#include <ros/console.h>
#include <ros/node_handle.h>
#include <ros/param.h>

#include <string>
#include <iostream>
#include <vector>
#include <limits>
#include <utility>

enum class ParamType { GLOBAL, NAMESPACED, PRIVATE };

std::string param_type_to_string(ParamType type) {
  static const std::string param_type_as_string[] = {"global", "namespaced", "private"};
  return param_type_as_string[static_cast<int>(type)];
}

void ros_check_and_exit() {
  if (!ros::ok()) {
    exit(1);
  }
}

void print_params(const ros::NodeHandle* nh, ParamType type) {
  double speed{0.0};
  std::string name;
  
  if (nh == nullptr) {
    if (ros::param::get("/robot_speed", speed)) {
      ROS_INFO_STREAM("\tRobot Speed: `" << speed << "` in global namespace");
    } else {
      ROS_WARN_STREAM("\tParameter `robot_speed` not found in global namespace");
    }

    if (ros::param::get("/robot_name", name)) {
      ROS_INFO_STREAM("\tRobot Name: `" << name << "` in global namespace");
    } else {
      ROS_WARN_STREAM("\tParameter `robot_name` not found in global namespace");
    }
    return;
  }

  if (type == ParamType::GLOBAL) {
    if (nh->getParam("/robot_speed", speed)) {
      ROS_INFO_STREAM("\tRobot Speed: `" << speed << "` in global namespace");
    } else {
      ROS_WARN_STREAM("\tParameter `robot_speed` not found in global namespace");
    }

    if (nh->getParam("/robot_name", name)) {
      ROS_INFO_STREAM("\tRobot Name: `" << name << "` in global namespace");
    } else {
      ROS_WARN_STREAM("\tParameter `robot_name` not found in global namespace");
    }
    return;
  } 

  const std::string ns = nh->getNamespace();

  if (nh->getParam("robot_speed", speed)) {
    ROS_INFO_STREAM("\tRobot Speed: `" << speed << "` in namespace: " << ns);
  } else {
    ROS_WARN_STREAM("\tParameter `robot_speed` not found in namespace: " << ns);
  }

  if (nh->getParam("robot_name", name)) {
    ROS_INFO_STREAM("\tRobot Name: `" << name << "` in namespace: " << ns);
  } else {
    ROS_WARN_STREAM("\tParameter `robot_name` not found in namespace: " << ns);
  }
}

void override_params(ros::NodeHandle* nh, const std::pair<double, std::string>& value, ParamType type) {

  // Get parameters
  ROS_INFO_STREAM("Checking " << param_type_to_string(type) << " parameters before overriding from code:");
  print_params(nh, type);

  const double speed = value.first;
  const std::string name = value.second;

  // Inform the user
  ROS_INFO_STREAM("Set " << param_type_to_string(type) << " parameters from code:");
  ROS_INFO_STREAM("\tSpeed: " << speed);
  ROS_INFO_STREAM("\tName: " << name);

  // Set parameters based on type
  if (nh == nullptr) {
    ros::param::set("/robot_speed", speed);
    ros::param::set("/robot_name", name);
  } else if (type == ParamType::GLOBAL) {
    nh->setParam("/robot_speed", speed);
    nh->setParam("/robot_name", name);
  }
  else {
    nh->setParam("robot_speed", speed);
    nh->setParam("robot_name", name);
  }

  // Get parameters
  ROS_INFO_STREAM("Checking " << param_type_to_string(type) << " parameters after overriding from code:");
  print_params(nh, type);

  if (type == ParamType::GLOBAL) {
    ROS_INFO("Verify with `rosparam get /robot_speed` and `rosparam get /robot_name`.");
  } else {
    ROS_INFO_STREAM("Verify with `rosparam get `" << nh->getNamespace() << "/robot_speed` and `rosparam get `" << nh->getNamespace() << "/robot_name`.");
  } 

  std::cout << "\nPress Enter to continue...";
  std::cin.get();  // Wait for input
  ros_check_and_exit();
}

int main(int argc, char** argv) {
  ros::init(argc, argv, "test_params_node");

  // The initial global parameters are set from the launch file.
  // Optionally it can be set in code in three ways as below and as demonstrated by override_params function.
  ros::NodeHandle global_nh1, global_nh2("/");
  //global_nh1.setParam("/robot_speed", 1.51);
  //global_nh1.setParam("/robot_name", "global_robot_1_set_in_code");

  //global_nh2.setParam("/robot_speed", 1.52);
  //global_nh2.setParam("/robot_name", "global_robot_2_set_in_code");

  //ros::param::set("/robot_speed", 1.53);
  //ros::param::set("/robot_name", "global_robot_3_set_in_code");

  static const std::vector<std::pair<double, std::string>> global_values = {
    {1.51, "global_robot_1_set_in_code"},
    {1.52, "global_robot_2_set_in_code"},
    {1.53, "global_robot_3_set_in_code"}
  };

  // The initial namespaced parameters are set from the launch file using `ns` attribute.
  // Optionally it can be set in code in two ways as below and as demonstrated by override_params function.
  ros::NodeHandle ns_nh1("/my_robot"), ns_nh2;
  //ns_nh1.setParam("robot_speed", 2.51);
  //ns_nh1.setParam("robot_name", "ns_robot_1_set_in_code");

  //ns_nh2.setParam("robot_speed", 2.52);
  //ns_nh2.setParam("robot_name", "ns_robot_2_set_in_code");
  
  static const std::vector<std::pair<double, std::string>> ns_values = {
    {2.51, "ns_robot_1_set_in_code"},
    {2.52, "ns_robot_2_set_in_code"}
  };

  // The initial private namespaced parameters are set from the launch file nested inside the node tag.
  // Optionally it can be set in code as below and as demonstrated by override_params function.
  ros::NodeHandle private_nh("~");
  //private_nh.setParam("robot_speed", 3.51);
  //private_nh.setParam("robot_name", "private_robot_1_set_in_code");
  
  static const std::vector<std::pair<double, std::string>> private_values = {
    {3.51, "private_robot_1_set_in_code"}
  };    

  while (ros::ok()) {
    std::cout << "\nChoose parameter scope to cycle through:\n";
    std::cout << "1. Global (/robot_speed, /robot_name)\n";
    std::cout << "2. Namespaced (/my_robot/robot_speed, /my_robot/robot_name)\n";
    std::cout << "3. Private (/my_robot/test_params_node/robot_speed, /my_robot/test_params/robot_name)\n";
    std::cout << "4. Exit\n";
    std::cout << "Enter choice (1/2/3/4): ";

    int choice;
    std::cin >> choice;  // Wait for input
    ros_check_and_exit();

    // Validate input
    while (std::cin.fail() || (choice < 1 || choice > 4)) {
      std::cout << "Invalid input. Please enter 1, 2, 3, or 4: ";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cin >> choice;  // Wait for input
      ros_check_and_exit();
    }

    // Clear input buffer
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (choice == 1) {
      override_params(&global_nh1, global_values[0], ParamType::GLOBAL);
      override_params(&global_nh2, global_values[1], ParamType::GLOBAL);
      override_params(nullptr, global_values[2], ParamType::GLOBAL);
    }
    else if (choice == 2) {
      override_params(&ns_nh1, ns_values[0], ParamType::NAMESPACED);
      override_params(&ns_nh2, ns_values[1], ParamType::NAMESPACED);
    }
    else if (choice == 3) {
      override_params(&private_nh, private_values[0], ParamType::PRIVATE);
    }
    else if (choice == 4) {
      std::cout << "Exiting...\n";
      break;
    }
  }

  return 0;
}

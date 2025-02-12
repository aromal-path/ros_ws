#include <ros/init.h>
#include <ros/console.h>
#include <ros/node_handle.h>
#include <ros/param.h>

#include <string>

void printParams(const ros::NodeHandle* nh) {
    double speed;
    std::string name;
    
    if (nh == nullptr) {
      if (ros::param::get("/robot_speed", speed)) {
        ROS_INFO_STREAM("Robot Speed: `" << speed << "` in global namespace");
      } else {
          ROS_WARN_STREAM("Parameter `robot_speed` not found in global namespace");
      }
  
      if (ros::param::get("/robot_name", name)) {
          ROS_INFO_STREAM("Robot Name: `" << name << "` in global namespace");
      } else {
          ROS_WARN_STREAM("Parameter `robot_name` not found in global namespace");
      }
      return;
    }

    const std::string ns = nh->getNamespace();

    if (nh->getParam("robot_speed", speed)) {
        ROS_INFO_STREAM("Robot Speed: `" << speed << "` in namespace: " << ns);
    } else {
        ROS_WARN_STREAM("Parameter `robot_speed` not found in namespace: " << ns);
    }

    if (nh->getParam("robot_name", name)) {
        ROS_INFO_STREAM("Robot Name: `" << name << "` in namespace: " << ns);
    } else {
        ROS_WARN_STREAM("Parameter `robot_name` not found in namespace: " << ns);
    }
}

int main(int argc, char** argv) {
    ros::init(argc, argv, "test_params_node");

    // ✅ The local namespaced parameters are set from the launch file using `ns` attribute.

    // ✅ The global parameters are set from the launch file. Optionally it can be set in code in two ways as below.
    ros::NodeHandle nh;
    //nh.setParam("/robot_speed", 1.5);
    //ros::param::set("/robot_name", "welding_robot_global");

    // ✅ The private namespaced parameters are set from the launch file nested inside the node tag. Optionally it can be set in code as below.
    ros::NodeHandle private_nh("~");
    //private_nh.setParam("robot_speed", 3.5);
    //private_nh.setParam("robot_name", "welding_robot_private");

    // ✅ Getting namespaced parameters
    ROS_INFO("Checking Namespaced Parameters:");
    printParams(&nh);

    // ✅ Getting private namespaced parameters
    ROS_INFO("Checking Private Parameters:");
    printParams(&private_nh);

    // ✅ Getting global parameters
    ROS_INFO("Checking Global Parameters:");
    printParams(nullptr);

    return 0;
}

#include <ros/init.h>
#include <ros/this_node.h>
#include <ros/console.h>
#include <ros/node_handle.h>
#include <ros/service_server.h>

#include <my_robot_package/AddTwoInts.h>
#include <my_robot_package/constants.h>

bool add(my_robot_package::AddTwoInts::Request &req,
         my_robot_package::AddTwoInts::Response &res) {
    res.sum = req.a + req.b;
    ROS_INFO("Received request: %ld + %ld = %ld", req.a, req.b, res.sum);
    return true;
}

int main(int argc, char **argv) {
    ros::init(argc, argv, "add_two_ints_server_node");

    ros::NodeHandle nh;
    ros::ServiceServer service = nh.advertiseService(my_robot_package::ADD_TWO_INTS_SERVICE_NAME, add);

    ROS_INFO_STREAM(ros::this_node::getName() << " ready to provide the service `" << service.getService() << "` add two integers.");
    ros::spin();
    return 0;
}

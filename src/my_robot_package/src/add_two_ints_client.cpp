#include <ros/init.h>
#include <ros/this_node.h>
#include <ros/console.h>
#include <ros/node_handle.h>
#include <ros/service_client.h>

#include <my_robot_package/AddTwoInts.h>
#include <my_robot_package/constants.h>

int main(int argc, char **argv) {
    ros::init(argc, argv, "add_two_ints_client_node");
    if (argc != 3) {
        ROS_ERROR("Usage: ROS_NAMESPACE=/my_robot rosrun my_robot_package add_two_ints_client X Y");
        return 1;
    }

    ros::NodeHandle nh;
    ros::ServiceClient client = nh.serviceClient<my_robot_package::AddTwoInts>(my_robot_package::ADD_TWO_INTS_SERVICE_NAME);

    my_robot_package::AddTwoInts srv;
    srv.request.a = atoll(argv[1]);
    srv.request.b = atoll(argv[2]);

    ROS_INFO_STREAM(ros::this_node::getName() << " ready to call the service `" << client.getService() << "` to add two integers.");

    if (client.call(srv)) {
        ROS_INFO("Sum: %ld", srv.response.sum);
    } else {
        ROS_ERROR("Failed to call service.");
        return 1;
    }
    return 0;
}

#include "ros/ros.h"
#include <std_msgs/Empty.h>

int main(int argc, char **argv)
{

  ros::init(argc, argv, "droneTakeOff");

  ros::NodeHandle n;

  ros::Publisher droneTakeOff_pub = n.advertise<std_msgs::Empty>("ardrone/takeoff", 1000);

  ros::Rate loop_rate(10);

  while (ros::ok())
  {

    std_msgs::Empty msg;

    droneTakeOff_pub.publish(msg);

    ros::spinOnce();

    loop_rate.sleep();


  }


  return 0;
}
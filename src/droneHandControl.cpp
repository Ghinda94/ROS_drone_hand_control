#include "ros/ros.h"
#include <std_msgs/Empty.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Point.h>
#include <iostream>
//using namespace std;

ros::NodeHandle n;

ros::Publisher droneTakeOff_pub = n.advertise<std_msgs::Empty>("ardrone/takeoff", 1000);

ros::Publisher droneLand_pub = n.advertise<std_msgs::Empty>("ardrone/land", 1000);

ros::Subscriber sub;

void left_hand_jointCallback(const geometry_msgs::Point &point)
{
	
	std_msgs::Empty msg;

	if(point.y > 0.0)
	{
		droneTakeOff_pub.publish(msg);
	}	
	else
	{
		droneLand_pub.publish(msg);
	}

	ROS_INFO("Y coord. is: [%f]", point.y);
}

int main(int argc, char **argv)
{
	ros::init(argc, argv, "droneHandControl");

	sub = n.subscribe("left_hand_joint", 1000, left_hand_jointCallback);

	ros::spin();

	return 0;
}
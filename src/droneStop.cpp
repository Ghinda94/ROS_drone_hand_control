#include <ros/ros.h>
#include <std_msgs/Empty.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Point.h>
#include "std_msgs/String.h"
#include <iostream>
#include <cmath>

class Subscribe_1
{
public:
	Subscribe_1()
	{
		sub = n.subscribe("stop_right_hand", 1000, &Subscribe_1::callback, this);
	}

	void callback(const std_msgs::String::ConstPtr& msg)
  	{
  		ROS_INFO("I heard 1 : [%s]", msg->data.c_str());
  	}

private:
  ros::NodeHandle n; 
  bool stop;
  ros::Subscriber sub;
};

class Subscribe_2
{
public:
	Subscribe_2()
	{
		sub = n.subscribe("stop_left_hand", 1000, &Subscribe_2::callback, this);
	}

	void callback(const std_msgs::String::ConstPtr& msg)
  	{
  		ROS_INFO("I heard 2 : [%s]", msg->data.c_str());
  	}

private:
  ros::NodeHandle n; 
  bool stop;
  ros::Subscriber sub;
};

int main(int argc, char **argv)
{
  //Initiate ROS
  ros::init(argc, argv, "dorneStop");

  //Create an object of class SubscribeAndPublish that will take care of everything
  Subscribe_1 sub_1;

  Subscribe_2 sub_2;

  ros::spin();

  return 0;
}
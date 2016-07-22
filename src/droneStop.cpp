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
		stop = true;
		sub = n.subscribe("stop_right_hand", 1000, &Subscribe_1::callback, this);
	}

	void callback(const std_msgs::String::ConstPtr& msg)
  	{
  		ROS_INFO("I heard 1 : [%s]", msg->data.c_str());

  		if(msg->data == "stop") 
  		{
  			stop = true;
  		}
  		else
  		{
  			stop = false;
  		}

  		ROS_INFO("Stop 1 : [%d]", stop);
  	}

  	bool getStop()
  	{
  		return stop;
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
		stop = true;
		sub = n.subscribe("stop_left_hand", 1000, &Subscribe_2::callback, this);
	}

	void callback(const std_msgs::String::ConstPtr& msg)
  	{
  		ROS_INFO("I heard 2 : [%s]", msg->data.c_str());

  		if(msg->data == "stop")
  		{
  			stop = true;
  		}
  		else
  		{
  			stop = false;
  		}

  		ROS_INFO("Stop 2 : [%d]", stop);
  	}

  	bool getStop()
  	{
  		return stop;
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

  ros::NodeHandle n;

  //Create an object of class SubscribeAndPublish that will take care of everything
  Subscribe_1 sub_1;

  Subscribe_2 sub_2;

  ros::Rate loop_rate(10);

  ros::Publisher stop_pub = n.advertise<geometry_msgs::Twist>("cmd_vel", 1000);

  while (ros::ok())
  {

	if(sub_1.getStop() == true && sub_2.getStop() == true)
	{
		ROS_INFO("STOP!");

		geometry_msgs::Twist msg;

		msg.linear.x = 0.0;
	    msg.linear.y = 0.0;
	    msg.linear.z = 0.0;

	    msg.angular.x = 0.0;
	    msg.angular.y = 0.0;
	    msg.angular.z = 0.0;

	    stop_pub.publish(msg);
	}
	else
	{
	  	ROS_INFO("go");
	}
	ros::spinOnce();
	loop_rate.sleep();
  }

  return 0;
}
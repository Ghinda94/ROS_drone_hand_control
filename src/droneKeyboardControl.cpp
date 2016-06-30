#include "ros/ros.h"
#include <std_msgs/Empty.h>
#include <geometry_msgs/Twist.h>
#include <iostream>
using namespace std;

int main(int argc, char **argv)
{
  
  ros::init(argc, argv, "droneKeyboardControl");

  ros::NodeHandle n;

  ros::Publisher droneKeyBoardControl_pub = n.advertise<geometry_msgs::Twist>("cmd_vel", 1000);

  ros::Publisher droneTakeOff_pub = n.advertise<std_msgs::Empty>("ardrone/takeoff", 1000);

  ros::Publisher droneLand_pub = n.advertise<std_msgs::Empty>("ardrone/land", 1000);

  ros::Rate loop_rate(10);

  geometry_msgs::Twist msg;

  std_msgs::Empty msg_takeoff_land;

  char c;

  while(ros::ok())
  {
  	cin.get(c);
  	switch(c)
  	{
  		case 'f':
  		{
  			msg.linear.x = 1.0;
  			msg.linear.y = 0.0;
  			msg.linear.z = 0.0;

  			msg.angular.x = 0.0;
  			msg.angular.y = 0.0;
  			msg.angular.z = 0.0;

  			droneKeyBoardControl_pub.publish(msg);
  			break;
  		}
  		case 'b':
  		{
  			msg.linear.x = -1.0;
  			msg.linear.y = 0.0;
  			msg.linear.z = 0.0;

  			msg.angular.x = 0.0;
  			msg.angular.y = 0.0;
  			msg.angular.z = 0.0;

  			droneKeyBoardControl_pub.publish(msg);
  			break;
  		}
  		case 's':
  		{
  			msg.linear.x = 0.0;
  			msg.linear.y = 0.0;
  			msg.linear.z = 0.0;

  			msg.angular.x = 0.0;
  			msg.angular.y = 0.0;
  			msg.angular.z = 0.0;

  			droneKeyBoardControl_pub.publish(msg);
  			break;
  		}
  		case 't':
    	{
    		droneTakeOff_pub.publish(msg_takeoff_land);
    		break;
    	}
    	case 'l':
    	{
    		droneLand_pub.publish(msg_takeoff_land);
    		break;
    	}
  	}

  	 ros::spinOnce();

    loop_rate.sleep();
  }

  return 0;
}
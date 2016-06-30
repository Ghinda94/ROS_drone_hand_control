#include "ros/ros.h"
#include <std_msgs/Empty.h>
#include <iostream>
using namespace std;

int main(int argc, char **argv)
{
  
  ros::init(argc, argv, "droneTakeOffandLand");

  ros::NodeHandle n;

  ros::Publisher droneTakeOff_pub = n.advertise<std_msgs::Empty>("ardrone/takeoff", 1000);

  ros::Publisher droneLand_pub = n.advertise<std_msgs::Empty>("ardrone/land", 1000);

  ros::Rate loop_rate(10);

  std_msgs::Empty msg;

  char c;

  while (ros::ok())
  {

    cin.get(c);

    switch(c)
    {
    	case 't':
    	{
    		droneTakeOff_pub.publish(msg);
    		break;
    	}
    	case 'l':
    	{
    		droneLand_pub.publish(msg);
    		break;
    	}
    }

    ros::spinOnce();

    loop_rate.sleep();
  }

  return 0;

}

#include <ros/ros.h>
#include <std_msgs/Empty.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Point.h>
#include <iostream>
#include <cmath>

class TakeOffAndLand
{
public:
  TakeOffAndLand()
  {
    //Topic you want to publish
    takeoff_pub = n.advertise<std_msgs::Empty>("ardrone/takeoff", 1000);

    land_pub = n.advertise<std_msgs::Empty>("ardrone/land", 1000);

    //Topic you want to subscribe
    sub = n.subscribe("torso_joint", 1000, &TakeOffAndLand::callback, this);
  }

  void callback(const geometry_msgs::Point &point)
  {
    std_msgs::Empty msg;

  	if(point.y < 0.0)
  	{
  		takeoff_pub.publish(msg);
  	}	
  	else
  	{
  		land_pub.publish(msg);
  	}

  	ROS_INFO("Y coord. is: [%f]", point.y);
  }

private:
  ros::NodeHandle n; 
  ros::Publisher takeoff_pub;
  ros::Publisher land_pub;
  ros::Subscriber sub;

};//End of class TakeOffAndLand


class Rotate
{
public:
  Rotate()
  {
    //Topic you want to publish
    rotate_pub = n.advertise<geometry_msgs::Twist>("cmd_vel", 1000);

    //Topic you want to subscribe
    sub = n.subscribe("right_hand_joint", 1000, &Rotate::callback, this);

  }

  void callback(const geometry_msgs::Point &point)
  {
    geometry_msgs::Twist msg;

    if(point.x < -0.6) // CCW rotation
    {
        msg.linear.x = 0.0;
        msg.linear.y = 0.0;
        msg.linear.z = 0.0;

        msg.angular.x = 0.0;
        msg.angular.y = 0.0;
        msg.angular.z = -0.1;
        
        rotate_pub.publish(msg);
    }
    else
    {
      if(point.x > 0.0) // CW rotation
      {
        msg.linear.x = 0.0;
        msg.linear.y = 0.0;
        msg.linear.z = 0.0;

        msg.angular.x = 0.0;
        msg.angular.y = 0.0;
        msg.angular.z = 0.1;

        rotate_pub.publish(msg);
      }
      else // stop!
      {
        msg.linear.x = 0.0;
        msg.linear.y = 0.0;
        msg.linear.z = 0.0;

        msg.angular.x = 0.0;
        msg.angular.y = 0.0;
        msg.angular.z = 0.0;

        rotate_pub.publish(msg);
      }
    }
  	ROS_INFO("X coord. is: [%f]", point.z);
  }

private:
  ros::NodeHandle n; 
  ros::Publisher rotate_pub;
  ros::Subscriber sub;

};//End of class SubscribeAndPublish

int main(int argc, char **argv)
{
  //Initiate ROS
  ros::init(argc, argv, "dorneTestCommands");

  
  TakeOffAndLand takeOffAndLand;

  Rotate rotate;

  ros::spin();

  return 0;
}
#include <ros/ros.h>
#include <std_msgs/Empty.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Point.h>
#include <iostream>
#include <cmath>

class SubscribeAndPublish
{
public:
  SubscribeAndPublish()
  {
    //Topic you want to publish
    flyUpDown_pub = n.advertise<geometry_msgs::Twist>("cmd_vel", 1000);

    //Topic you want to subscribe
    sub = n.subscribe("left_hand_joint", 1000, &SubscribeAndPublish::callback, this);

  }

  void callback(const geometry_msgs::Point &point)
  {
    geometry_msgs::Twist msg;
    if(point.y > 0.6) // fly up
    {
      msg.linear.x = 0.0;
      msg.linear.y = 0.0;
      msg.linear.z = 0.5;

      msg.angular.x = 0.0;
      msg.angular.y = 0.0;
      msg.angular.z = 0.0;

      flyUpDown_pub.publish(msg);
    }
    else
    {
      if(point.y < 0.0) // fly down
      {
        msg.linear.x = 0.0;
        msg.linear.y = 0.0;
        msg.linear.z = -0.5;

        msg.angular.x = 0.0;
        msg.angular.y = 0.0;
        msg.angular.z = 0.0;

        flyUpDown_pub.publish(msg);
      }
      else // stop!
      {
        msg.linear.x = 0.0;
        msg.linear.y = 0.0;
        msg.linear.z = 0.0;

        msg.angular.x = 0.0;
        msg.angular.y = 0.0;
        msg.angular.z = 0.0;

        flyUpDown_pub.publish(msg);
      }
    }
  	ROS_INFO("Y coord. is: [%f]", point.y);
  }

private:
  ros::NodeHandle n; 
  ros::Publisher flyUpDown_pub;
  ros::Subscriber sub;

};//End of class SubscribeAndPublish

int main(int argc, char **argv)
{
  //Initiate ROS
  ros::init(argc, argv, "dorneFlyUpDown");

  //Create an object of class SubscribeAndPublish that will take care of everything
  SubscribeAndPublish SAPObject;

  ros::spin();

  return 0;
}
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
    rotate_pub = n.advertise<geometry_msgs::Twist>("cmd_vel", 1000);

    //Topic you want to subscribe
    sub = n.subscribe("right_hand_joint", 1000, &SubscribeAndPublish::callback, this);

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
        msg.angular.z = -1.0;
        
        rotate_pub.publish(msg);
    }
    else
    {
      if(point.x > 0.4) // CW rotation
      {
        msg.linear.x = 0.0;
        msg.linear.y = 0.0;
        msg.linear.z = 0.0;

        msg.angular.x = 0.0;
        msg.angular.y = 0.0;
        msg.angular.z = 1.0;

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
  ros::init(argc, argv, "dorneRotate");

  //Create an object of class SubscribeAndPublish that will take care of everything
  SubscribeAndPublish SAPObject;

  ros::spin();

  return 0;
}
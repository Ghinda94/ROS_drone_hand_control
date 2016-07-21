#include <ros/ros.h>
#include <std_msgs/Empty.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Point.h>
#include <std_msgs/String.h>
#include <iostream>
#include <cmath>

class SubscribeAndPublish
{
public:
  SubscribeAndPublish()
  {   
      //Topic you want to publish
      rotate_pub = n.advertise<geometry_msgs::Twist>("cmd_vel", 1000);

      stopRight = n.advertise<std_msgs::String>("stop_right_hand", 1000);

      //Topic you want to subscribe
      sub = n.subscribe("left_hand_joint", 1000, &SubscribeAndPublish::callback, this);

  }

  void callback(const geometry_msgs::Point &point)
  {
    geometry_msgs::Twist msg;

    ros::Rate loop_rate(10);

    std::stringstream ss;
    std_msgs::String s;


    if(point.x < -0.2) // CCW rotation
    {
      ss << "go";
      s.data = ss.str();
      stopRight.publish(s);

      msg.linear.x = 0.0;
      msg.linear.y = 0.0;
      msg.linear.z = 0.0;

      msg.angular.x = 0.0;
      msg.angular.y = 0.0;
      msg.angular.z = -0.5;
      
      rotate_pub.publish(msg);
    }
    else
    {
      if(point.x > 0.4) // CW rotation
      {
        ss << "go";
        s.data = ss.str();
        stopRight.publish(s);

        msg.linear.x = 0.0;
        msg.linear.y = 0.0;
        msg.linear.z = 0.0;

        msg.angular.x = 0.0;
        msg.angular.y = 0.0;
        msg.angular.z = 0.5;

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

        ss << "stop";
        s.data = ss.str();
        stopRight.publish(s);
      }
    }
  	ROS_INFO("X coord. is: [%f]", point.x);
  }

private:
  ros::NodeHandle n; 
  ros::Publisher rotate_pub;
  ros::Subscriber sub;
  ros::Publisher stopRight;

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
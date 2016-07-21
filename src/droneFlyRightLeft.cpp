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
    flyRightLeft_pub = n.advertise<geometry_msgs::Twist>("cmd_vel", 1000);

    stopLeft = n.advertise<std_msgs::String>("stop_left_hand", 1000);

    //Topic you want to subscribe
    sub = n.subscribe("right_hand_joint", 1000, &SubscribeAndPublish::callback, this);

  }

  void callback(const geometry_msgs::Point &point)
  {
    
    geometry_msgs::Twist msg;
    ros::Rate loop_rate(100);

    std::stringstream ss;
    std_msgs::String s;

    // move forward
    if(point.x > 0.2)
    {
      ss << "go";
      s.data = ss.str();
      stopLeft.publish(s);

      msg.linear.x = 0.0;
      msg.linear.y = -0.2;
      msg.linear.z = 0.0;

      msg.angular.x = 0.0;
      msg.angular.y = 0.0;
      msg.angular.z = 0.0;

      flyRightLeft_pub.publish(msg);
    }
    else
    {
      if(point.x < -0.4)
      {
        ss << "go";
        s.data = ss.str();
        stopLeft.publish(s);

        msg.linear.x = 0.0;
        msg.linear.y = 0.2;
        msg.linear.z = 0.0;

        msg.angular.x = 0.0;
        msg.angular.y = 0.0;
        msg.angular.z = 0.0;

        flyRightLeft_pub.publish(msg);
      }
      else // stop!
      {
        if(point.x < 0.2 && point.x > -0.4 && point.y < 0.6 && point.y > 0.0)
        {
          msg.linear.x = 0.0;
          msg.linear.y = 0.0;
          msg.linear.z = 0.0;

          msg.angular.x = 0.0;
          msg.angular.y = 0.0;
          msg.angular.z = 0.0;

          flyRightLeft_pub.publish(msg);
                    
          ss << "stop";
          s.data = ss.str();
          stopLeft.publish(s);
        }
      }
    }
  	ROS_INFO("X coord. is: [%f]", point.x);
  }

private:
  ros::NodeHandle n; 
  ros::Publisher flyRightLeft_pub;
  ros::Subscriber sub;
  ros::Publisher stopLeft;

};//End of class SubscribeAndPublish

int main(int argc, char **argv)
{
  //Initiate ROS
  ros::init(argc, argv, "dorneFlyRightLeft");

  //Create an object of class SubscribeAndPublish that will take care of everything
  SubscribeAndPublish SAPObject;

  ros::spin();

  return 0;
}
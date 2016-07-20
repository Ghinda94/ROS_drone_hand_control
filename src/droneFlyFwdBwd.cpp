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

    firstTime = true;

    //Topic you want to publish
    flyFwdBwd_pub = n.advertise<geometry_msgs::Twist>("cmd_vel", 1000);

    //Topic you want to subscribe
    sub = n.subscribe("right_hand_joint", 1000, &SubscribeAndPublish::callback, this);

  }

  void callback(const geometry_msgs::Point &point)
  {
    
    geometry_msgs::Twist msg;
    ros::Rate loop_rate(100);

    // if(firstTime)
    // {
    //   actualPos = point.z;
    //   firstTime = false;
    // }
    // else
    // {
      //float diff = 0.0;
      //diff = point.z - actualPos;
      //if(diff > 0.05) // move forward
      if(point.y > 0.6)
      {
        msg.linear.x = 0.2;
        msg.linear.y = 0.0;
        msg.linear.z = 0.0;

        msg.angular.x = 0.0;
        msg.angular.y = 0.0;
        msg.angular.z = 0.0;

        flyFwdBwd_pub.publish(msg);
        //loop_rate.sleep();

        //actualPos = point.z;
      }
      else
      {
        //if(diff < -0.05) // move backward
        if(point.y < 0.0)
        {
          msg.linear.x = -0.2;
          msg.linear.y = 0.0;
          msg.linear.z = 0.0;

          msg.angular.x = 0.0;
          msg.angular.y = 0.0;
          msg.angular.z = 0.0;

          flyFwdBwd_pub.publish(msg);
          //loop_rate.sleep();

          //actualPos = point.z;
        }
        else // stop!
        {
          msg.linear.x = 0.0;
          msg.linear.y = 0.0;
          msg.linear.z = 0.0;

          msg.angular.x = 0.0;
          msg.angular.y = 0.0;
          msg.angular.z = 0.0;

          flyFwdBwd_pub.publish(msg);
          //loop_rate.sleep();
        }
      }
    //}
  	ROS_INFO("Z coord. is: [%f]", point.z);
  }

private:
  ros::NodeHandle n; 
  ros::Publisher flyFwdBwd_pub;
  ros::Subscriber sub;
  float actualPos;
  bool firstTime;

};//End of class SubscribeAndPublish

int main(int argc, char **argv)
{
  //Initiate ROS
  ros::init(argc, argv, "dorneFlyFwdBwd");

  //Create an object of class SubscribeAndPublish that will take care of everything
  SubscribeAndPublish SAPObject;

  ros::spin();

  return 0;
}
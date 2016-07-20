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
      ros::Rate loop_rate(10);
      
      while (n.ok())
      {

        //Topic you want to publish
        rotate_pub = n.advertise<geometry_msgs::Twist>("cmd_vel", 1000);

        //Topic you want to subscribe
        sub = n.subscribe("right_hand_joint", 1000, &SubscribeAndPublish::callback, this);
      
        ros::spinOnce();

        loop_rate.sleep();
      }
  }

  void callback(const geometry_msgs::Point &point)
  {
    geometry_msgs::Twist msg;

    ros::Rate loop_rate(10);

    if(point.x < -0.6) // CCW rotation
    {
      msg.linear.x = 0.0;
      msg.linear.y = 0.0;
      msg.linear.z = 0.0;

      msg.angular.x = 0.0;
      msg.angular.y = 0.0;
      msg.angular.z = -0.1;
      
      rotate_pub.publish(msg);

      //ros::spinOnce();

      //loop_rate.sleep();
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

        //ros::spinOnce();

        //loop_rate.sleep();
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

        //ros::spinOnce();

        //loop_rate.sleep();
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

  ros::Rate loop_rate(10);

  while (ros::ok())
  {
    //Create an object of class SubscribeAndPublish that will take care of everything
    SubscribeAndPublish SAPObject;

    ros::spinOnce();

    loop_rate.sleep();
  }

  return 0;
}
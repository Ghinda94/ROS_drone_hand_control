#include <ros/ros.h>
#include <std_msgs/Empty.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Point.h>
#include <iostream>

class SubscribeAndPublish
{
public:
  SubscribeAndPublish()
  {
    //Topic you want to publish
    takeoff_pub = n.advertise<std_msgs::Empty>("ardrone/takeoff", 1000);

    land_pub = n.advertise<std_msgs::Empty>("ardrone/land", 1000);

    //Topic you want to subscribe
    sub = n.subscribe("torso_joint", 1000, &SubscribeAndPublish::callback, this);
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

};//End of class SubscribeAndPublish

int main(int argc, char **argv)
{
  //Initiate ROS
  ros::init(argc, argv, "dorneHandControlTakeoffAndLand");

  //Create an object of class SubscribeAndPublish that will take care of everything
  SubscribeAndPublish SAPObject;

  ros::spin();

  return 0;
}
#include <ros/ros.h>
#include <tf/transform_listener.h>
#include <geometry_msgs/Twist.h>

int main(int argc, char** argv)
{
  
	ros::init(argc, argv, "tfListener");

	ros::NodeHandle node;

	ros::Publisher left_hand_joint = node.advertise<geometry_msgs::Point>("left_hand_joint", 1000);

	tf::TransformListener listener;
	
	ros::Rate rate(50.0); // frequency of operation

	while (node.ok())
	{

		// Transforms declared for left_hand joint

		tf::StampedTransform  transform_left_hand;

		try
		{
			listener.lookupTransform("/left_hand_1", "/openni_depth_frame",ros::Time(0), transform_left_hand);
		}
		catch (tf::TransformException &ex) 
	    {
	        ROS_ERROR("%s",ex.what());
	        ros::Duration(0.10).sleep();
	        continue;
	    }

	    geometry_msgs::Point left_hand_pose;

	    left_hand_pose.x = transform_left_hand.getOrigin().x();
	    left_hand_pose.y = transform_left_hand.getOrigin().y();
	    left_hand_pose.z = transform_left_hand.getOrigin().z();

	    left_hand_joint.publish(left_hand_pose);

	    rate.sleep();
	}

	return 0;
}
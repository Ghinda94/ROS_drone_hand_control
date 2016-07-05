#include <ros/ros.h>
#include <tf/transform_listener.h>
#include <geometry_msgs/Twist.h>

int main(int argc, char** argv)
{
  
	ros::init(argc, argv, "rightHandJointListener");

	ros::NodeHandle node;

	ros::Publisher right_hand_joint = node.advertise<geometry_msgs::Point>("right_hand_joint", 1000);

	tf::TransformListener listener;
	
	ros::Rate rate(50.0); // frequency of operation

	while (node.ok())
	{

		// Transforms declared for torso joint

		tf::StampedTransform  transform_right_hand;

		try
		{
			listener.lookupTransform("/right_hand_2", "/openni_depth_frame",ros::Time(0), transform_right_hand);
		}
		catch (tf::TransformException &ex) 
	    {
	        ROS_ERROR("%s",ex.what());
	        ros::Duration(0.10).sleep();
	        continue;
	    }

	    geometry_msgs::Point right_hand_pose;

	    right_hand_pose.x = transform_right_hand.getOrigin().x();
	    right_hand_pose.y = transform_right_hand.getOrigin().y();
	    right_hand_pose.z = transform_right_hand.getOrigin().z();

	    right_hand_joint.publish(right_hand_pose);

	    rate.sleep();
	}

	return 0;
}
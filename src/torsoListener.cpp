#include <ros/ros.h>
#include <tf/transform_listener.h>
#include <geometry_msgs/Twist.h>

int main(int argc, char** argv)
{
  
	ros::init(argc, argv, "torsoListener");

	ros::NodeHandle node;

	ros::Publisher torso_joint = node.advertise<geometry_msgs::Point>("torso_joint", 1000);

	tf::TransformListener listener;
	
	ros::Rate rate(50.0); // frequency of operation

	while (node.ok())
	{

		// Transforms declared for torso joint

		tf::StampedTransform  transform_torso;

		try
		{
			listener.lookupTransform("/torso_2", "/openni_depth_frame",ros::Time(0), transform_torso);
		}
		catch (tf::TransformException &ex) 
	    {
	        ROS_ERROR("%s",ex.what());
	        ros::Duration(0.10).sleep();
	        continue;
	    }

	    geometry_msgs::Point torso_pose;

	    torso_pose.x = transform_torso.getOrigin().x();
	    torso_pose.y = transform_torso.getOrigin().y();
	    torso_pose.z = transform_torso.getOrigin().z();

	    torso_joint.publish(torso_pose);

	    rate.sleep();
	}

	return 0;
}
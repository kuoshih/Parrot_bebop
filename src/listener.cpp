/*
 * Copyright (c) 2010, Willow Garage, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the Willow Garage, Inc. nor the names of its
 *       contributors may be used to endorse or promote products derived from
 *       this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

// %Tag(FULLTEXT)%
// %Tag(INCLUDES)%
#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include "nav_msgs/Odometry.h"
#include "sensor_msgs/Image.h"
#include "geometry_msgs/Twist.h"
#include "std_msgs/Empty.h"

// %EndTag(INCLUDES)%

// %Tag(INIT)%
void callback1(const ros::TimerEvent&);
ros::Publisher pub;
ros::Publisher takeOff;
geometry_msgs::Twist msg; 
int counter=0;



void callback1(const ros::TimerEvent&)
{// update maker location and publish it. 


	if(counter==2*10)
	{

		system( "rostopic pub -1 /bebop/takeoff std_msgs/Empty");
    		ROS_INFO("Bebop: Takeoff!");
	}

	if(counter==6*10)
	{

		msg.linear.x =0.1;
		msg.linear.y =0;
		msg.linear.z =0;
		msg.angular.z =0;
    		ROS_INFO("Bebop: Forward!");/**/
	}

	if(counter==8*10)
	{
		msg.linear.x =-0.1;
		msg.linear.y =0;
		msg.linear.z =0;
		msg.angular.z =0;
    		ROS_INFO("Bebop: Backward!");/**/
	}

	if(counter==11*10)
	{
		msg.linear.x =0;
		msg.linear.y =0;
		msg.linear.z =0;
		msg.angular.z =0;
    		ROS_INFO("Bebop: STOP");/**/
	}

	if(counter==12*10)
	{
		system( "rostopic pub -1 /bebop/land std_msgs/Empty");
    		ROS_INFO("Bebop: Landing!");
	}


	pub.publish(msg);

    counter++;
	
	
}

void odomCallback(const nav_msgs::Odometry::ConstPtr& msg)
{
    //ROS_INFO("X: [%f], Y: [%f], Z: [%f]", msg->pose.pose.position.x,msg->pose.pose.position.y,msg->pose.pose.position.z);
}

void msgCallback(const sensor_msgs::Image::ConstPtr& msg)
{
    //ROS_INFO("height = %d, width = %d",msg->height, msg->width);
    //ROS_INFO("Image_data = %d",msg->data[0]);
}

int main( int argc, char** argv )
{


  ros::init(argc, argv, "Bebop_CODE");
  ros::NodeHandle n;
  ros::Rate r(1);
  // create a timer callback
  ros::Timer timer1 = n.createTimer(ros::Duration(0.1), callback1);
  // create callbacks of odometery, images, vel_command.
  ros::Subscriber sub3 = n.subscribe("bebop/odom", 1000, odomCallback);
  ros::Subscriber cam_sub = n.subscribe("/bebop/image_raw",100,msgCallback);
  pub = n.advertise<geometry_msgs::Twist>("bebop/cmd_vel", 10);


 
  ros::spin();

}



#include <ros/ros.h>
#include "geometry_msgs/Twist.h"
#include <sensor_msgs/Joy.h>
#include <stdio.h>


class TeleopUgv
{
public:
  TeleopUgv();

private:
  void joyCallback(const sensor_msgs::Joy::ConstPtr& joy);
  
  ros::NodeHandle nh_;

  int linear_, angular_;
  double l_scale_, a_scale_;
  ros::Publisher vel_pub_;
  ros::Subscriber joy_sub_;
  
};


TeleopUgv::TeleopUgv():
  linear_(1),
  angular_(0),
  l_scale_(1),
  a_scale_(1)
{
  // Get the private (~) parameters
  ros::param::param("~axis_linear", linear_, linear_);
  ros::param::param("~axis_angular", angular_, angular_);
  ros::param::param("~scale_angular", a_scale_, a_scale_);
  ros::param::param("~scale_linear", l_scale_, l_scale_);
  printf("Parameters: axis_linear=%d, axis_angular=%d, scale_angular=%f, scale_linear=%f\n",linear_,angular_,a_scale_,l_scale_);
  vel_pub_ = nh_.advertise<geometry_msgs::Twist>("joy/cmd_vel", 1);

  joy_sub_ = nh_.subscribe<sensor_msgs::Joy>("joy", 10, &TeleopUgv::joyCallback, this);

}

void TeleopUgv::joyCallback(const sensor_msgs::Joy::ConstPtr& joy)
{
  geometry_msgs::Twist vel;
  vel.linear.x = l_scale_*joy->axes[linear_];
  vel.linear.y = 0;
  vel.angular.z = a_scale_*joy->axes[angular_];

  vel_pub_.publish(vel);
}


int main(int argc, char** argv)
{
  ros::init(argc, argv, "teleop_ugv");
  TeleopUgv teleop_ugv;

  ros::spin();
}

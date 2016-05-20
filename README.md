# nre_joy
Joystick teleoperation for NPS robots.

This package is meant to be used with the [ROS joy](http://wiki.ros.org/joy) package.  It is an adaptation of the 
[Writing a Teleoperation Node for a Linux-Supported Joystick](http://wiki.ros.org/joy/Tutorials/WritingTeleopNode) tutorial included with that package.

# Dependencies
 * The joy package - which should come with your ROS installation
 
# Installation
Installing the package from source follows the typical catkin/github workflow.  If we assume 
that /path/to/your/catkin_ws = ~/catkin_ws

```bash
cd ~/catkin_ws/src
git clone git@github.com:bsb808/nre_joy.git
cd ~/catkin_ws
rosdep update
rosdep install nre_joy
catkin_make
```
You can check that the package is installed by attempting to run the executable...

```bash
rosrun nre_joy teleop_ugv_joy 
```

# Nodes
## teleop_ugv_joy
This node does the mapping from the joy node to the cmd_vel that is sent to the robot.  
The concept is that the joystick displacements are published to the **joy** topic by the 
joy_node, which is the driver that talks to the USB joystick.  The teleop_ugv_joy node subscribes to this topic.  
When it receives a message it maps the joystick displacements to a Twist message (linear.x velocity and angular.z velocity)
based on the parameters described below.  It then publishes the resulting Twist message on the joy/cmd_vel topic.

Parameters:
 * axis_linear (int): index of the joystick array message determining which axis of the joystick is mapped to the Twist.linear.x velocity.
 * axis_angular (int): index of the joystick array message determining the axis of the joystick to makp to the Twist.angular.z value.
 * scale_angular (double): linear scaling of joystick displacment (-1 to 1) to angular velocity command.
 * scale_liinear (double): ditto for linear velocity command.

### Usage
Launch files are supplied which start the nodes for the NPS robots (P3AT and Husky) based on using the Logitech F310 USB gamepad.
These launch files set the parameters, remap the node publish topics and also start the joy_node

# Limitations
 * Only tested with Indigo

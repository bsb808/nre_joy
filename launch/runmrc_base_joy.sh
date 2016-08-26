#/bin/bash
export BASE_IP=$(ifconfig wlan0 | grep 'inet addr' | cut -d: -f2 | awk '{print $1}')
echo "Setting environmental variable for BASE_IP="$BASE_IP
export ROS_MASTER_URI=http://${BASE_IP}:11311
export ROS_IP=${BASE_IP}
export ROS_HOSTNAME=${BASE_IP}
echo "----------------------------------------"
env | grep ROS
echo "----------------------------------------"
roslaunch nre_joy teleop_ugv_joy_p3at.launch
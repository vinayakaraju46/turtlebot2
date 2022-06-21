
# Turtlesim

Turtlesim is a tool made for teaching ROS and ROS packages.



## Start roscore:

roscore


## To install and start the turtlesim:
sudo apt-get install ros-noetic-turtlesim
## Run turtlesim:
rosrun turtlesim turtlesim_node

## Steady State Error

Steady state error is calculated by applying derivative to error signal.

When only P controller is used, error is simply multiplied with Kp (gain). Kp is obtained by tuning.

error = Distance between goal_pose and the current_pose (set_point - process_signal).

velocity_msgs.linear.x = Kp*error;

steady_state_error = derivative(error)

### Plot

X axis -> Time

Y axis -> Derivative of error

![Steady_stateError](https://user-images.githubusercontent.com/30818966/174637483-cbdffeb0-7ba1-48dc-a703-377e11bd572e.png)

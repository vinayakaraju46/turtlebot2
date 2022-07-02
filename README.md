
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


## PID Controller

Proportional-Integral-Derivative (PID) control is the most common control algorithm used in industry and has been universally accepted in industrial control. The popularity of PID controllers can be attributed partly to their robust performance in a wide range of operating conditions and partly to their functional simplicity, which allows engineers to operate them in a simple, straightforward manner.

As the name suggests, PID algorithm consists of three basic coefficients; proportional, integral and derivative which are varied to get optimal response. Closed loop systems, the theory of classical PID and the effects of tuning a closed loop control system are discussed in this paper. The PID toolset in LabVIEW and the ease of use of these VIs is also discussed.

please visit https://www.ni.com/en-in/innovations/white-papers/06/pid-theory-explained.html to understand PID controllers in depth 

## Output

![ezgif com-gif-maker](https://user-images.githubusercontent.com/30818966/176988746-73532728-b11a-457e-8c78-d92bc8d2ad3f.gif)



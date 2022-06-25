#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "turtlesim/Pose.h"
#include <sstream>

using namespace std;

ros::Publisher velocityPublisher;
turtlesim::Pose turtlesim_pose;
const double PI = 3.14159265359;

void poseCallBack(const turtlesim::Pose::ConstPtr& pose_message);
void move(double speed, double distance, bool isForward);
void rotate(double angular_speed, double relative_angle, bool clockWise);
double degrees2Radians(double angle_in_degrees);
void moveToGoal(turtlesim::Pose goal_pose, double distance_tolerance);

int main(int argc, char** argv) {
    // int x,y;
    ros::init(argc, argv, "turtleMove");
    ros::NodeHandle n;
    turtlesim::Pose goal_pose;

    velocityPublisher = n.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 1000);
    ros::Subscriber pose_subscriber = n.subscribe("/turtle1/pose", 10, poseCallBack);

    ROS_INFO("\n\n\n*******Start testing*******\n");
    ros::Rate loop_rate(0.5);
    move(1.0, 4, true);
    rotate(10, 90, true);

    ros::param::get("/x_goal", goal_pose.x);
    ros::param::get("/y_goal", goal_pose.y);
    cout << "x: " << goal_pose.x << " y: " << goal_pose.y << endl;
    // goal_pose.x = 1;
    // goal_pose.y = 1;
    goal_pose.theta=0;
    moveToGoal(goal_pose, 0.01);

    cout << "Hello Turtle Bot" << endl;

    ros::spin();
    return 0;
}


void poseCallBack(const turtlesim::Pose::ConstPtr& pose_message) {
    turtlesim_pose.x = pose_message->x;
    turtlesim_pose.y = pose_message->y;
    turtlesim_pose.theta = pose_message->theta;
}

void move(double speed, double distance, bool isForward) {
    geometry_msgs::Twist vel_msgs;

    if(isForward) {
        vel_msgs.linear.x = abs(speed);
    } else {
        vel_msgs.linear.x = -abs(speed);
    }
    vel_msgs.linear.y = 0;
    vel_msgs.linear.z = 0;
    vel_msgs.angular.x = 0;
    vel_msgs.angular.y = 0;
    vel_msgs.angular.z = 0;

    double t0 = ros::Time::now().toSec();
    double current_distance = 0.0;
    ros::Rate loop_rate(100);
    do {
        velocityPublisher.publish(vel_msgs);
        double t1 = ros::Time::now().toSec();
        current_distance = speed * (t1-t0);
        ros::spinOnce();
        loop_rate.sleep();
        cout << (t1-t0) << ", " << current_distance << ", " << distance << endl;
    } while (current_distance < distance);
    vel_msgs.linear.x = 0;
    velocityPublisher.publish(vel_msgs);
}

void rotate(double angular_speed, double relative_angle, bool clockWise) {
    geometry_msgs::Twist vel_msgs;
    vel_msgs.linear.x = 0;
    vel_msgs.linear.y = 0;
    vel_msgs.linear.z = 0;
    vel_msgs.angular.x = 0;
    vel_msgs.angular.y = 0;

    if(!clockWise) {
        vel_msgs.angular.z = -abs(degrees2Radians(angular_speed));
    } else {
        vel_msgs.angular.z = abs(degrees2Radians(angular_speed));
    }
    
    double t0 = ros::Time::now().toSec();
    double current_angle = 0.0;
    ros::Rate loop_rate(10);

    do {
        velocityPublisher.publish(vel_msgs);
        double t1 = ros::Time::now().toSec();
        current_angle = angular_speed * (t1-t0);
        ros::spinOnce();
        loop_rate.sleep();
    } while (current_angle < relative_angle);

    vel_msgs.angular.z = 0;
    velocityPublisher.publish(vel_msgs);

}

double degrees2Radians(double angle_in_degrees) {
    return angle_in_degrees * PI /180.0;
}

double getDistance(double x1, double y1, double x2, double y2) {
    return sqrt(pow((x1-x2), 2)+pow((y1-y2), 2));
}

void moveToGoal(turtlesim::Pose goal_pose, double distance_tolerance) {
    geometry_msgs::Twist vel_msgs;

    ros::Rate loop_rate(10);
    double E = 0.0;
    do {
        double Kp_Linear = 1.0;
        double Kp_angular = 4.0;

        double e = getDistance(turtlesim_pose.x, turtlesim_pose.y, goal_pose.x, goal_pose.y);
        
        vel_msgs.linear.x = (Kp_Linear*e);
        vel_msgs.linear.y = 0;
        vel_msgs.linear.z = 0;

        vel_msgs.angular.x = 0;
        vel_msgs.angular.y = 0;
        vel_msgs.angular.z = Kp_angular*(atan2(goal_pose.y - turtlesim_pose.y, goal_pose.x - turtlesim_pose.x) -  turtlesim_pose.theta);
        velocityPublisher.publish(vel_msgs);
        ros::spinOnce();
        loop_rate.sleep();
    } while(getDistance(turtlesim_pose.x, turtlesim_pose.y, goal_pose.x, goal_pose.y) > distance_tolerance);
    cout << "goal reached" << endl;
    vel_msgs.linear.x = 0;
    vel_msgs.angular.z = 0;
    velocityPublisher.publish(vel_msgs);
}
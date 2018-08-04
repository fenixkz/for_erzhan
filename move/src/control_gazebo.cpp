#include "ros/ros.h"
#include "std_msgs/Float64.h"
#include "std_msgs/Int64.h"
#include "robot_control/coord.h"

    double X;
    int change = 1;
    int i = 0;
    int prevState;
    double pos1;
    double pos2;
    double pos3;
    double pos4;
    double pos5;

void coordCallback(const robot_control::coord::ConstPtr& msg) {
	 
X = msg->x;
	
	change = msg->y;
	if ((change == 0) && (change != prevState)){
		i = i+1;
		if (i>4){
			i = 0;
		}
	}
//ROS_INFO("x: %f number: %d", X, i);
ROS_INFO(" ");
prevState = change;

}

int main(int argc, char **argv){
  
ros::init(argc, argv, "rotate");

ros::NodeHandle n;
ros::NodeHandle nh;
ros::NodeHandle nh1;
ros::NodeHandle nh2;
ros::NodeHandle nh3;
ros::NodeHandle nh4;

ros::Subscriber sub = n.subscribe("coord", 1000, coordCallback);

ros::Publisher pub = nh.advertise<std_msgs::Float64>("/robot/joint1_position_controller/command", 100);
ros::Publisher pub1 = nh1.advertise<std_msgs::Float64>("/robot/joint2_position_controller/command", 100);
ros::Publisher pub2 = nh2.advertise<std_msgs::Float64>("/robot/joint3_position_controller/command", 100);
ros::Publisher pub3 = nh3.advertise<std_msgs::Float64>("/robot/joint4_position_controller/command", 100);
ros::Publisher pub4 = nh4.advertise<std_msgs::Float64>("/robot/joint5_position_controller/command", 100);  


ros::Rate loop_rate(10);
while (ros::ok()){
std_msgs::Float64 msg;

if (i == 0){
msg.data = pos1 + 0.05*(X-519)*1.97/512;

if (msg.data >2.1){
msg.data = 2.1;
}else if(msg.data < -2.1){
msg.data = -2.1;
}
pub.publish(msg);
pos1 = msg.data;
}


if (i == 1){
msg.data = pos2 + 0.05*(X-519)*1.97/512;

if (msg.data >2.1){
msg.data = 2.1;
}else if(msg.data < -2.1){
msg.data = -2.1;
}
pub1.publish(msg);
pos2 = msg.data;
}

if (i == 2){
msg.data = pos3 + 0.05*(X-519)*1.97/512;

if (msg.data >2.1){
msg.data = 2.1;
}else if(msg.data < -2.1){
msg.data = -2.1;
}
pub2.publish(msg);
pos3 = msg.data;
}



if (i == 3){
msg.data = pos4 + 0.05*(X-519)*1.97/512;

if (msg.data > 2.1){
msg.data = 2.1;
}else if(msg.data < -2.1){
msg.data = -2.1;
}
pub3.publish(msg);
pos4 = msg.data;
}


if (i == 4){
msg.data = pos5 + 0.05*(X-519)*1.97/512;

if (msg.data >2.1){
msg.data = 2.1;
}else if(msg.data < -2.1){
msg.data = -2.1;
}
pub4.publish(msg);
pos5 = msg.data;
}
ros::spinOnce();

loop_rate.sleep();
}
}




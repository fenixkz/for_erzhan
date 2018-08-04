#include "ros/ros.h"
#include "std_msgs/Float64.h"
#include "std_msgs/Int64.h"
#include "dynamixel_msgs/JointState.h"
#include "robot_control/coord.h"
#include "robot_control/accelerometr.h"
#include "sensor_msgs/JointState.h"

	double X;
	double prevX = -10;
	double Y;
	double K;
	double pos1;
	double pos2;
	double pos3;
	double pos4;
	double pos5;



	int key = 0;
	int key2 = 0;
	int key3 = 0;
	int key4 = 0;
	int key5 = 0;
	int change = 1;
	int prevState;
	
	double prevK;
	int i = 0;
	int j =0;
	int button1 = 0;
	int prevButton = 5;
	int j2a = 0;
	int isStuck = 0;




void jointCallback(const dynamixel_msgs::JointState::ConstPtr& msg) {
if (key == 0){
 pos1 = msg->current_pos;
key = 1;
}

ROS_INFO("position of the 1st joint: %f ", pos1);



}

void joint1Callback(const dynamixel_msgs::JointState::ConstPtr& msg) {
if (key2 == 0){
 pos2 = msg->current_pos;
key2 = 1;
}
//if ((pos2b - prevPos2b < 0.03) || (pos2b - prevPos2b > -0.03)){
//		isMoving = 0;
//	}

//	if((pos2b - prevPos2b > 0.03) || (pos2b - prevPos2b < -0.03)){
//		isMoving = 1;
//	}
//ROS_INFO("position of 2nd joint: %f", pos2);
ROS_INFO(" ");

}

void joint2Callback(const dynamixel_msgs::JointState::ConstPtr& msg) {
if (key3 == 0){
 pos3 = msg->current_pos;
key3 = 1;
}
//ROS_INFO("position of the 3rd joint: %f", pos3);
ROS_INFO(" ");
}

void joint3Callback(const dynamixel_msgs::JointState::ConstPtr& msg) {
if (key3 == 0){
 pos4 = msg->current_pos;
key3 = 1;
}
ROS_INFO(" ");
//ROS_INFO("position of the 4th joint: %f", pos4);
}

void joint4Callback(const dynamixel_msgs::JointState::ConstPtr& msg) {
if (key4 == 0){
 pos5 = msg->current_pos;
key4 = 1;
}
//ROS_INFO("position of the 5th joint: %f", pos5);
ROS_INFO(" ");
}

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


void accelCallback(const robot_control::accelerometr::ConstPtr& msg) {

Y = msg->y;
K = msg->x;
	if ((K > 13000) && (prevK <13000)){
		j = j+1;
		if (j>4){
			j = 0;
		}
		}
	if ((K < -13000) && (prevK > -13000)){
		j--;
		if (j < 0){
			j = 4;
		}
		}

//ROS_INFO("Y: %f j: %d", Y, j);
ROS_INFO(" ");
prevK = K;
}

void buttonCb(const std_msgs::Int64::ConstPtr& msg) {

button1 = msg->data;



if (button1 == 1 && prevButton == 0){
		j2a++;
	}

//ROS_INFO(" button = %d        prevButton = %d          j2a = %d", button1, prevButton, j2a);
ROS_INFO(" ");
prevButton = button1;
}






int main(int argc, char **argv){
ros::init(argc, argv, "rotate");

sensor_msgs::JointState joint_state;

ros::NodeHandle nh;
ros::NodeHandle nh1;
ros::NodeHandle nh2;
ros::NodeHandle nh3;
ros::NodeHandle nh4;
ros::NodeHandle node;
ros::NodeHandle nh5;



ros::NodeHandle n;
ros::NodeHandle acc;


ros::NodeHandle n1;
ros::NodeHandle n2;
ros::NodeHandle n3;
ros::NodeHandle n4;
ros::NodeHandle n5;
ros::NodeHandle button;

ros::Subscriber sub = n.subscribe("coord", 1000, coordCallback);
ros::Subscriber asub = acc.subscribe("accel", 1000, accelCallback);



//ros::Publisher joint_pub = node.advertise<sensor_msgs::JointState>("joint_states", 10);
ros::Publisher pub = nh.advertise<std_msgs::Float64>("/tilt_controller/command", 100);
ros::Publisher pub1 = nh1.advertise<std_msgs::Float64>("/joint1_controller/command", 100);
ros::Publisher pub2 = nh2.advertise<std_msgs::Float64>("/joint2_controller/command", 100);
ros::Publisher pub3 = nh3.advertise<std_msgs::Float64>("/joint3_controller/command", 100);
ros::Publisher pub4 = nh4.advertise<std_msgs::Float64>("/joint4_controller/command", 100);
ros::Publisher pub5 = nh5.advertise<std_msgs::Int64>("motorN", 100);



ros::Subscriber sub1 = n1.subscribe("/tilt_controller/state", 1000, jointCallback);
ros::Subscriber sub2 = n2.subscribe("/joint1_controller/state", 1000, joint1Callback);
ros::Subscriber sub3 = n3.subscribe("/joint2_controller/state", 1000, joint2Callback);
ros::Subscriber sub4 = n4.subscribe("/joint3_controller/state", 1000, joint3Callback);
ros::Subscriber sub5 = n5.subscribe("/joint4_controller/state", 1000, joint4Callback);
ros::Subscriber sub6 = button.subscribe("/isPressed", 1000, buttonCb);


ros::Rate loop_rate(10);
while (ros::ok()){
std_msgs::Float64 msg;
std_msgs::Int64 number;







if ((j2a % 2) == 0){
number.data = i;
pub5.publish(number);
if (i == 0){
msg.data = pos1 + 0.05*(X-519)*1.97/512;
pub.publish(msg);
if (msg.data >2.1){
msg.data = 2.1;
}else if(msg.data < -2.1){
msg.data = -2.1;
}



//ROS_INFO("msg.data = %f            pos1 = %f", msg.data, pos1);
pos1 = msg.data;



}
if (i == 1){
msg.data = pos2 + 0.05*(X-519)*1.97/512;
pub1.publish(msg);

if (msg.data >2.1){
msg.data = 2.1;
}else if(msg.data < -2.1){
msg.data = -2.1;
}

pos2 = msg.data;

//if ((pos2 - pos2b > 0.03) || (pos2 - pos2b < -0.03)){
//	goalPos = 1;
//}

//if ((pos2 - pos2b < 0.03 && msg.data - pos2b > 0) || (pos2 - pos2b > -0.03 && pos2 - pos2b < 0)){
//	goalPos = 0;
//}

}

if (i == 2){
msg.data = pos3 + 0.05*(X-519)*1.97/512;
pub2.publish(msg);

if (msg.data >2.1){
msg.data = 2.1;
}else if(msg.data < -2.1){
msg.data = -2.1;
}

pos3 = msg.data;
//joint_state.position[1] = pos3;
}

if (i == 3){
msg.data = pos4 + 0.05*(X-519)*1.97/512;
pub3.publish(msg);

if (msg.data >2.1){
msg.data = 2.1;
}else if(msg.data < -2.1){
msg.data = -2.1;
}

pos4 = msg.data;
//joint_state.position[2] = pos4;
}

if (i == 4){
msg.data = pos5 + 0.05*(X-519)*1.97/512;
pub4.publish(msg);

if (msg.data >2.1){
msg.data = 2.1;
}else if(msg.data < -2.1){
msg.data = -2.1;
}

pos5 = msg.data;
//joint_state.position[3] = pos5;
}
}
if ((j2a % 2) == 1){
number.data = j;
pub5.publish(number);
	if (j == 0){
 	if ((Y>3000) || (Y<-3000)){
	msg.data = pos1 + 0.1*Y*1.97/16000;

	}else{
	msg.data = pos1;
	}
pub.publish(msg);

if (msg.data >2.1){
msg.data = 2.1;
}else if(msg.data < -2.1){
msg.data = -2.1;
}

	pos1 = msg.data;
}

	if (j == 1){
	if ((Y>3000) || (Y<-3000)){
	msg.data = pos2 + 0.1*Y*1.97/16000;

	}else{
	msg.data = pos2;
	}
pub1.publish(msg);

if (msg.data >2.1){
msg.data = 2.1;
}else if(msg.data < -2.1){
msg.data = -2.1;
}

	pos2 = msg.data;
	}

	if (j == 2){
	if ((Y>3000) || (Y<-3000)){
	msg.data = pos3 + 0.1*Y*1.97/16000;

	}else{
	msg.data = pos3;
	}
pub2.publish(msg);

if (msg.data >2.1){
msg.data = 2.1;
}else if(msg.data < -2.1){
msg.data = -2.1;
}

	pos3 = msg.data;
	}

	if (j == 3){
	if ((Y>3000) || (Y<-3000)){
	msg.data = pos4 + 0.1*Y*1.97/16000;

	}else{
	msg.data = pos4;
	}
pub3.publish(msg);

if (msg.data >2.1){
msg.data = 2.1;
}else if(msg.data < -2.1){
msg.data = -2.1;
}

	pos4 = msg.data;
	}

	if (j == 4){
	if ((Y>3000) || (Y<-3000)){
	msg.data = pos5 + 0.1*Y*1.97/16000;

	}else{
	msg.data = pos5;
	}
pub4.publish(msg);

if (msg.data >2.1){
msg.data = 2.1;
}else if(msg.data < -2.1){
msg.data = -2.1;
}

	pos5 = msg.data;
	}
}

//pub6.publish(st);


ros::spinOnce();

loop_rate.sleep();
}
}

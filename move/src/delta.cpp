#include "ros/ros.h"
#include "std_msgs/Float64.h"
#include "nidaq/fsrInput.h"
    double x;
    double time0;
    double time_now;
    double time1;
    void butCallBack(const nidaq::fsrInput::ConstPtr& msg){
      x = msg->i0;
    }
int main(int argc, char **argv){
    ros::init(argc, argv, "delta");
    ros::NodeHandle nh;
    ros::NodeHandle n;
    ros::Publisher pub = nh.advertise<std_msgs::Float64>("/delta", 100);
    ros::Subscriber sub = n.subscribe("/Ayan6216", 100, butCallBack);
    ros::Rate loop_rate(0.5);
    std_msgs::Float64 msg;
    while (ros::ok()){
    while (ros::ok()){
    if( x > 1.2){
    msg.data = 0.1;
    pub.publish(msg);
    break;
    }
    ros::spinOnce();

    }
    ros::spinOnce();
    loop_rate.sleep();
    }

    return 0;
}

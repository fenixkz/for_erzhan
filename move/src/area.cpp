#include <ros/ros.h>
#include <std_msgs/Float64.h>

int contact_1;
int contact_2;
int contact_3;
int contact_4;
int contact_5;

void contCallBack(const robot_control::contact::ConstPtr& msg){
  contact_1 = msg->contact1;
  contact_2 = msg->contact2;
  contact_3 = msg->contact3;
  contact_4 = msg->contact4;
  contact_5 = msg->contact5;
}

int main(int argc, char **argv){
    init(argc, argv, "area");
    NodeHandle sub;
    Subscriber contact = sub.subscribe("/contact", 10, contCallBack);
    Publisher total_area = pub.advertise<std_msgs::Float64>("/Total_area", 100);
    Rate loop_rate(25);

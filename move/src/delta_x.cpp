#include <std_msgs/Float64.h>
#include <ros/ros.h>
using namespace std;
using namespace ros;
double x;
double y;


void xCb(const std_msgs::Float64::ConstPtr& msg){
  x = msg->data;
}

void yCb(const std_msgs::Float64::ConstPtr& msg){
  y = msg->data;
}

double sqr(double z){
  return z*z;
}

int main(int argc, char **argv){
  init(argc, argv, "delta_x");

  NodeHandle sub;
  NodeHandle pub;
  Subscriber x_coord = sub.subscribe("/x_coord", 100, xCb);
  Subscriber y_coord = sub.subscribe("/y_coord", 100, yCb);
  Publisher delta_x = pub.advertise<std_msgs::Float64>("/delta_x", 100);
  std_msgs::Float64 xdata;
  Rate loop_rate(50);
  while (ok()){
    xdata.data = sqrt(sqr(x - 1.81697) + sqr(y - 1.4287));
    delta_x.publish(xdata);
    spinOnce();
    loop_rate.sleep();
  }
  return 0;
}

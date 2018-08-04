#include "ros/ros.h"
#include "dynamixel_msgs/JointState.h"
#include "robot_control/rigid.h"
#include "robot_control/newtactile.h"
#include "std_msgs/Bool.h"
#include "std_msgs/Int64.h"
#include "robot_control/contact.h"
using namespace ros;

  robot_control::contact cont;
  robot_control::contact cont1;
  bool terminate = false;
  double tactile_1;
  double tactile_2;
  double tactile_3;
  double tactile_4;
  double tactile_5;
  double tactile_1_;
  double tactile_2_;
  double tactile_3_;
  double tactile_4_;
  double tactile_5_;

  double T = 0.2;
  double dt = 0.02;
  Publisher pub;
  robot_control::newtactile middle;
  robot_control::newtactile message;
  robot_control::newtactile message_;

  double time0;
  double time_now;
  double time1;

  double highPassFilter(double z, double z_, double out){
    double res = (out + z - z_)*T/(T + dt);
    return res;
  }
  void termCallBack(const std_msgs::Bool::ConstPtr& msg){
    terminate = msg->data;
  }
  void tactileCallBack(const robot_control::newtactile::ConstPtr& msg){
    tactile_1_ = tactile_1;
    tactile_2_ = tactile_2;
    tactile_3_ = tactile_3;
    tactile_4_ = tactile_4;
    tactile_5_ = tactile_5;
    tactile_1 = msg->first;
    tactile_2 = msg->second;
    tactile_3 = msg->third;
    tactile_4 = msg->fourth;
    tactile_5 = msg->fifth;
    //message_.first = message.first;
    //message_.second = message.second;
    //message_.third = message.third;
    //message_.fourth = message.fourth;
    //message_.fifth = message.fifth;

    message.first = highPassFilter(tactile_1, tactile_1_, message.first);
    message.second = highPassFilter(tactile_2, tactile_2_, message.second);
    message.third = highPassFilter(tactile_3, tactile_3_, message.third);
    message.fourth = highPassFilter(tactile_4, tactile_4_, message.fourth);
    message.fifth = highPassFilter(tactile_5, tactile_5_, message.fifth);

    //middle.first = highPassFilter(message.first, message_.first, middle.first);
    //middle.first = highPassFilter(message.second, message_.second, middle.second);
    //middle.first = highPassFilter(message.third, message_.third, middle.third);
    //middle.first = highPassFilter(message.fourth, message_.fourth, middle.fourth);
    //middle.first = highPassFilter(message.first, message_.first, middle.first);
    if (!terminate){
    if (message.first < -20){
      cont.contact1 = 1;
    }
    if (cont.contact1 == 1 && message.first > 100){
      cont.contact1 = 0;
    }
    if (message.second < -20){
      cont.contact2 = 1;
    }
    if (cont.contact2 == 1 && message.second > 100){
      cont.contact2 = 0;
    }
    if (message.third < -20){
      cont.contact3 = 1;
    }
  if (cont.contact3 == 1 && message.third > 100){
      cont.contact3 = 0;
    }
    if (message.fourth < -20){
      cont.contact4 = 1;
    }
    if (cont.contact4 == 1 && message.fourth > 100){
      cont.contact4 = 0;
    }
    if (message.fifth < -20){
      cont.contact5 = 1;
    }
    if (cont.contact5 == 1 && message.fifth > 100){
      cont.contact5 = 0;
    }
  }
  }

  int main(int argc, char **argv){
    ros::init(argc, argv, "isContact");


    cont1.contact1 = 0;
    cont1.contact2 = 0;
    cont1.contact3 = 0;
    cont1.contact4 = 0;
    cont1.contact5 = 0;

    NodeHandle tac;
    NodeHandle nh;
      Publisher pub1 = nh.advertise<robot_control::contact>("/contact", 10);
      //Publisher pub = nh.advertise<robot_control::newtactile>("/HP", 10);
    Subscriber tact = tac.subscribe("/tactile", 1000, tactileCallBack);
    Subscriber term = tac.subscribe("/isTerminate", 1000, termCallBack);
    cont.contact1 = 0;
    cont.contact2 = 0;
    cont.contact3 = 0;
    cont.contact4 = 0;
    cont.contact5 = 0;
    Rate loop_rate(50);
    Duration(1.0).sleep();
    while(ok()){

    time0 = ros::Time::now().toSec();

   if (terminate){

     time1 = time0 + 2;
     terminate = false;
   }
    // pub.publish(message);
    if (time1 >= time0){

           cont.contact1 = 0;
           cont.contact2 = 0;
           cont.contact3 = 0;
           cont.contact4 = 0;
           cont.contact5 = 0;
    }

      pub1.publish(cont);

      spinOnce();
      loop_rate.sleep();
    }
    return 0;
  }

#include <ros/ros.h>
#include <robot_control/tactile.h>
#include <robot_control/contact.h>
#include "dynamixel_msgs/JointState.h"
#include "stdlib.h"
#include <string>
#include <std_msgs/Float64.h>
#include <std_msgs/String.h>
#include <std_msgs/Bool.h>
#include <std_msgs/Int64.h>
using namespace ros;
using namespace std;
bool isMove;
bool isContact = false;
bool identified = false;

double deriv;
int del = 0;
int del2 = 0;
double a;
int maxa = 450;
double b;
int maxb = 405;
double c;
int maxc = 500;
double d;
int maxd = 525;
double e;
int maxe = 450;
int area = 0;


int experiment = 0;

int flag = 0;
int area_init = 0;
int aS = 0;
int bS = 0;
int cS = 0;
int dS = 0;
int eS = 0;
int forcea;
int forceb;
int forcec;
int forced;
int forcee;
int k = 0;

double load_1;
double load_2;
double load_3;
double load_4;
double load_5;
double load_total;
double load_now;
double load_init;
double center;
double x;
double x_init = 0;
double y;
double y_init = 0;
double a_dif;

int key = 0;

  int a1 = 0;
  double dx = 0;

int contact_1;
int contact_2;
int contact_3;
int contact_4;
int contact_5;


double time_init;
double time_final;

void motor1(const dynamixel_msgs::JointState::ConstPtr& msg){
    load_1 = msg->load;
}
void motor2(const dynamixel_msgs::JointState::ConstPtr& msg){
    load_2 = msg->load;
}
void motor3(const dynamixel_msgs::JointState::ConstPtr& msg){
    load_3 = msg->load;
}
void motor4(const dynamixel_msgs::JointState::ConstPtr& msg){
    load_4 = msg->load;
}
void motor5(const dynamixel_msgs::JointState::ConstPtr& msg){
    load_5 = msg->load;
    isMove = msg->is_moving;
}

void deltaCallBack(const std_msgs::Float64::ConstPtr& msg){

  del++;
}

void xCb(const std_msgs::Float64::ConstPtr& msg){
  x = msg->data;
}
void yCb(const std_msgs::Float64::ConstPtr& msg){
  y = msg->data;
}
/*void tactileCallBack(const robot_control::tactile::ConstPtr& msg){

    a = msg->first;
    if (a < 0){
        a = 0;
    }else{
      a = a*350/440;
    }
        b = msg->second;
        if (b < 0){
            b = 0;
        }else{
          b = b*350/360;
        }
            c = msg->third;
            if (c < 0){
                c = 0;
            }else{
              c = c*350/450;
            }
                d = msg->fourth;
                if (d < 0){
                    d = 0;
                }else{
                  d = d*350/480;
                }
                    e = msg->fifth;
                    if (e < 0) {
                        e = 0;
                    }else{
                      e = e*350/410;
                    }
}*/

void contCallBack(const robot_control::contact::ConstPtr& msg){
  contact_1 = msg->contact1;
  contact_2 = msg->contact2;
  contact_3 = msg->contact3;
  contact_4 = msg->contact4;
  contact_5 = msg->contact5;
}


std_msgs::Bool terminated;

int main(int argc, char **argv){
    init(argc, argv, "cop");
    NodeHandle sub;
    NodeHandle R;
    Publisher RigOrSoft = R.advertise<std_msgs::String>("/RoS", 100);
    NodeHandle pub;
    terminated.data = false;
    //Subscriber cop =  sub.subscribe("/tactile", 100, tactileCallBack);
    Subscriber mot1 = sub.subscribe("/motortom2m/state", 100, motor1);
    Subscriber mot2 = sub.subscribe("/joint2/state", 100, motor2);
    Subscriber mot3 = sub.subscribe("/joint4/state", 100, motor3);
    Subscriber mot4 = sub.subscribe("/joint6/state", 100, motor4);
    Subscriber mot5 = sub.subscribe("/end/state", 100, motor5);
    Subscriber xx = sub.subscribe("/x_coord", 100, xCb);
    Subscriber yy = sub.subscribe("/y_coord", 100, yCb);
    Subscriber delta = sub.subscribe("/delta", 100, deltaCallBack);
    Subscriber contact = sub.subscribe("/contact", 10, contCallBack);
    Publisher total_area = pub.advertise<std_msgs::Float64>("/Total_area", 100);
    Publisher total_load = pub.advertise<std_msgs::Float64>("/Total_load", 100);
    Publisher term = pub.advertise<std_msgs::Bool>("/isTerminate", 100);
    Publisher exper = pub.advertise<std_msgs::Int64>("/experimentN", 100);
    std_msgs::Float64 msg;
    std_msgs::Float64 msg1;
    Rate loop_rate(25);
    std_msgs::String result;
    std_msgs::Int64 expNum;
    while (ok()){

        load_total = abs(load_1) + abs(load_2) + abs(load_3) + abs(load_4) + abs(load_5);

  /*      if (a < 340){
            aS = 49;
        }else{
            aS = 0;
        }
            if (b < 310){
            bS = 49;
        }else{
            bS = 0;
        }
                if (c < 320){
            cS = 49;
        }else{
            cS = 0;
        }
                    if (d < 330){
            dS = 49;
        }else{
            dS = 0;
        }
                        if (e < 340){
            eS = 49;
        }else{
            eS = 0;
        }
*/

    if (contact_1 == 1){
      aS = 49;
    }else{
      aS = 0;
    }

          if (contact_2 == 1){
        bS = 49;
            }else{
          bS = 0;
            }
            if (contact_3 == 1){
                cS = 49;
                  }else{
                      cS = 0;
                  }


            if (contact_4 == 1){
              dS = 49;
                  }else{
                    dS = 0;
                    }


                if (contact_5 == 1){
                    eS = 49;
                    }else{
                        eS = 0;
                          }
        //forcea = maxa - a;
        //forceb = maxb - b;
        //forcec = maxc - c;
        //forced = maxd - d;
        //forcee = maxe - e;
        area = aS + bS + cS + dS + eS;

        //ROS_INFO("a: %f   b: %f   c: %f  d: %f  e: %f",a,b,c,d,e);

        if (area != 0){
          isContact = true;
        }else{
          isContact = false;
        }

        if (isContact && key == 0){
          x_init = x;
          y_init = y;
          load_init = load_total;
          Duration(0.1).sleep();
          area_init = area;

          key++;
          time_init = Time::now().toSec();
          ROS_INFO("area init: %d    x_init: %f   y_init: %f    load_init: %f   time_init: %f", area_init,x_init,y_init, load_init, time_init);

        }
        //ROS_INFO("%f", sqrt((x - x_init)*(x - x_init) + (y - y_init)*(y - y_init)));




        if (load_total > 0.4 && load_total > load_init && isContact){
        //  ROS_INFO("area %d   dx: %f", area,sqrt((x - x_init)*(x - x_init) + (y - y_init)*(y - y_init)));

          if (area > area_init && sqrt((x - x_init)*(x - x_init) + (y - y_init)*(y - y_init)) > 0.09){
            identified = true;
            a1 = area;
            dx = sqrt((x - x_init)*(x - x_init) + (y - y_init)*(y - y_init));
            result.data = "Object is soft";
          }else{
            result.data = "Object is rigid";
          }
        }


        //center = (forcea*3+forceb*11+forcec*19+forced*27+forcee*35)/(forcea + forceb + forcec + forced + forcee);
        //ROS_INFO("Area is: %d mm^2", area);
        //ROS_INFO("Total load is: %f", load_total);

        if (identified && flag == 0 && isContact){
          ROS_INFO("area %d   dx: %f", a1, dx);
          RigOrSoft.publish(result);
          terminated.data = true;
          term.publish(terminated);
          load_now = load_total;
          time_final = Time::now().toSec();
          experiment++;
          ROS_INFO("delta torque is  %f", (load_now - load_init)/(time_final - time_init));
          identified = false;
          flag = 1;
        }


        if (load_total > 0.8 && flag == 0){
        RigOrSoft.publish(result);
        ROS_INFO("Publishing to terminate...");
        terminated.data = true;
        term.publish(terminated);
        ROS_INFO("area %d   dx: %f", area, sqrt((x - x_init)*(x - x_init) + (y - y_init)*(y - y_init)));
        time_final = Time::now().toSec();
        deriv = (load_total - load_init)/(time_final - time_init);
        ROS_INFO("delta time  %f   and  delta torque  %f", (time_final - time_init), deriv);
        experiment++;
        if ((time_final - time_init) < 1){
          ROS_INFO("Object is rigid");
        }else{
          ROS_INFO("Object is soft");
        }
        flag = 1;
      }
      if(!isContact){
        k = 0;
        key = 0;
      }
      //cout<<Time::now().toSec()<<"\n";
      //ROS_INFO("%f", Time::now().toSec());
      if (!isContact && load_total < 0.4 && flag == 1){
        flag = 0;
        ROS_INFO("Starting again....");
      }
        msg.data = load_total;
        msg1.data = area;
        expNum.data = experiment;
        exper.publish(expNum);
        total_load.publish(msg);
        total_area.publish(msg1);
        ros::spinOnce();
        loop_rate.sleep();
    }
    return 0;
}

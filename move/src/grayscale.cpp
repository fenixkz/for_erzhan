#include <ros/ros.h>
#include <cv_bridge/cv_bridge.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <sensor_msgs/image_encodings.h>
#include <cv_bridge/cv_bridge.h>
#include <robot_control/tactile.h>
    uchar tacti[5];
void tactCallBack(const robot_control::tactile::ConstPtr& msg){

    tacti[0] = 255 - msg->first*255/483 ;
    tacti[1] = 255 - msg->second*255/457 ;
    tacti[2] = 255 - msg->third*255/543 ;
    tacti[3] = 255 - msg->fourth*255/580 ;
    tacti[4] = 255 - msg->fifth*255/481 ;
    if(msg->first < 0){
        tacti[0] = 255;
    }
    if(msg->second < 0){
        tacti[1] = 255;
    }
    if(msg->third < 0){
        tacti[2] = 255;
    }
    if(msg->fourth < 0){
        tacti[3] = 255;
    }
    if(msg->fifth < 0){
        tacti[4] = 255;
    }
}

int main(int argc, char **argv){
ros::init(argc, argv, "grayscale");
ros::NodeHandle nh;
ros::NodeHandle sub;
ROS_INFO("Good");
ros::Subscriber tact = sub.subscribe("/tactile", 100, tactCallBack);
image_transport::ImageTransport it(nh);
image_transport::Publisher pub = it.advertise("camera/image", 1);

ros::Rate loop_rate(10);
while (nh.ok()){
  //  ROS_INFO("%d %d %d %d %d", tacti[0], tacti[1], tacti[2], tacti[3], tacti[4]);
uchar array[5] = {tacti[0], tacti[1], tacti[2], tacti[3], tacti[4]};
cv::Mat tactile(1, 5, CV_8UC1, array);
//std::cout << "M = " << std::endl << " " << tactile << std::endl << std::endl;
sensor_msgs::ImagePtr msg = cv_bridge::CvImage(std_msgs::Header(), "mono8", tactile).toImageMsg();




    pub.publish(msg);
  
       ros::spinOnce();
      loop_rate.sleep();
}
return 0;

}


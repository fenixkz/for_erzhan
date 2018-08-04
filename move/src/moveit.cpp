#include <moveit/move_group_interface/move_group.h>
#include <moveit/planning_scene_interface/planning_scene_interface.h>
#include <moveit/move_group_interface/move_group_interface.h>
#include <moveit_msgs/DisplayRobotState.h>
#include <moveit_msgs/DisplayTrajectory.h>
#include <std_msgs/Float64.h>
#include <moveit_msgs/AttachedCollisionObject.h>
#include <moveit_msgs/CollisionObject.h>
#include <moveit_visual_tools/moveit_visual_tools.h>
#include <dynamixel_msgs/JointState.h>
#include <tf/transform_broadcaster.h>
#include <math.h>
#include <std_msgs/Bool.h>
#include <robot_control/contact.h>

double delta = 0;
int key = 0;
int key1 = 0;
int key2 = 0;
robot_control::contact cont;
double q4;
double xangle;
double yangle;
double zangle;
bool terminated = false;
/*void deltaCallBack(const std_msgs::Float64::ConstPtr& msg){
  delta = msg->data;
  key = key + 1;
}*/

double sqr(double x){
  return x*x;
}

void termCallBack(const std_msgs::Bool::ConstPtr& msg){
  terminated = msg->data;
}



static void toEulerAngle(const tf::Quaternion& q, double& roll, double& pitch, double& yaw)
{
	// roll (x-axis rotation)
	double sinr = +2.0 * (q.w() * q.x() + q.y() * q.z());
	double cosr = +1.0 - 2.0 * (q.x() * q.x() + q.y() * q.y());
	roll = atan2(sinr, cosr);

	// pitch (y-axis rotation)
	double sinp = +2.0 * (q.w() * q.y() - q.z() * q.x());
	if (fabs(sinp) >= 1)
		pitch = copysign(M_PI / 2, sinp); // use 90 degrees if out of range
	else
		pitch = asin(sinp);

	// yaw (z-axis rotation)
	double siny = +2.0 * (q.w() * q.z() + q.x() * q.y());
	double cosy = +1.0 - 2.0 * (q.y() * q.y() + q.z() * q.z());
	yaw = atan2(siny, cosy);
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "move_group_interface_tutorial");
  ros::NodeHandle node_handle;
  ros::NodeHandle nh;
  ros::NodeHandle node;

  ros::AsyncSpinner spinner(0);
  spinner.start();
  //ros::Subscriber sub = nh.subscribe("/delta", 100, deltaCallBack);

  ros::Subscriber sub = node.subscribe("/isTerminate", 100, termCallBack);

  static const std::string PLANNING_GROUP = "arm";
  // The :move_group_interface:`MoveGroup` class can be easily
  // setup using just the name of the planning group you would like to control and plan for.
  moveit::planning_interface::MoveGroupInterface move_group(PLANNING_GROUP);

  // We will use the :planning_scene_interface:`PlanningSceneInterface`
  // class to add and remove collision objects in our "virtual world" scene
  moveit::planning_interface::PlanningSceneInterface planning_scene_interface;

  // Raw pointers are frequently used to refer to the planning group for improved performance.
  const robot_state::JointModelGroup *joint_model_group =
      move_group.getCurrentState()->getJointModelGroup(PLANNING_GROUP);

  namespace rvt = rviz_visual_tools;
  moveit_visual_tools::MoveItVisualTools visual_tools("base_link");
  visual_tools.deleteAllMarkers();

  // Remote control is an introspection tool that allows users to step through a high level script
  // via buttons and keyboard shortcuts in RViz
  visual_tools.loadRemoteControl();

  // RViz provides many types of markers, in this demo we will use text, cylinders, and spheres
  Eigen::Affine3d text_pose = Eigen::Affine3d::Identity();
  text_pose.translation().z() = 1.75;
  visual_tools.publishText(text_pose, "MoveGroupInterface Demo", rvt::WHITE, rvt::XLARGE);

  // Batch publishing is used to reduce the number of messages being sent to RViz for large visualizations
  visual_tools.trigger();


  geometry_msgs::PoseStamped target_pose1;
  //target_pose1 = move_group.getCurrentPose();



  geometry_msgs::PoseStamped target_pose2;
  target_pose2.pose.position.x = 0;
  target_pose2.pose.position.y = 0;
  target_pose2.pose.orientation.w = target_pose1.pose.orientation.w;
  target_pose2.pose.orientation.z = target_pose1.pose.orientation.z;
  tf::TransformListener listener;
  ros::Rate loop_rate(10);
  while (ros::ok()){

    tf::StampedTransform transform;
    target_pose1 = move_group.getCurrentPose();
  //  std::cout<<target_pose1;



    try{
      listener.lookupTransform("/world", "/sensor_frame", ros::Time(0), transform);
    }catch (tf::TransformException &ex) {
       ROS_ERROR("%s",ex.what());

        continue;
      }

    toEulerAngle(transform.getRotation(), xangle, yangle, zangle);




      delta = 0.3;

//ROS_INFO("%d", terminated);
    if (!terminated){
      target_pose1.pose.position.x = target_pose1.pose.position.x + delta*cos(zangle);
      target_pose1.pose.position.y = target_pose1.pose.position.y + delta*sin(zangle);

    }else{
      /*
      target_pose1.pose.position.x = 1.97902;
      target_pose1.pose.position.y = 1.35829;
      target_pose1.pose.position.z = 0.02;
      target_pose1.pose.orientation.x = 0;
      target_pose1.pose.orientation.y = 0;
      target_pose1.pose.orientation.z = 0.665284;
      target_pose1.pose.orientation.w = 0.746591;*/
      target_pose1.pose.position.x = 1.81697;
      target_pose1.pose.position.y = 1.4287;
      target_pose1.pose.position.z = 0.02;
      target_pose1.pose.orientation.x = 0;
      target_pose1.pose.orientation.y = 0;
      target_pose1.pose.orientation.z = 0.705478;
      target_pose1.pose.orientation.w = 0.708732;
      /*
      target_pose1.pose.position.x = 2.09377;
      target_pose1.pose.position.y = -0.0068;
      target_pose1.pose.position.z = 0.02;
      target_pose1.pose.orientation.x = 0;
      target_pose1.pose.orientation.y = 0;
      target_pose1.pose.orientation.z = 0.00076699;
      target_pose1.pose.orientation.w = 1;*/
      terminated = false;
  }

    //ROS_INFO("%f", sqrt(sqr(target_pose2.pose.position.x - target_pose1.pose.position.x) + sqr(target_pose2.pose.position.y - target_pose1.pose.position.y)));
    //ROS_INFO("x %f y %f", target_pose1.pose.position.x, target_pose1.pose.position.y);


    if (sqrt(sqr(target_pose1.pose.position.x - target_pose2.pose.position.x) + sqr(target_pose1.pose.position.y - target_pose2.pose.position.y)) > 0.02) {

      //target_pose1.pose.orientation.z = move_group.getCurrentPose().pose.orientation.z;
      //target_pose1.pose.orientation.w = move_group.getCurrentPose().pose.orientation.w;
      ROS_INFO("New pose");
      //std::cout<<move_group.getCurrentPose();
      //std::cout<<"\n";
      //std::cout<<target_pose1;



  // Put some random reachable pose
  //target_pose1 = move_group.getRandomPose();
  move_group.setApproximateJointValueTarget(target_pose1);
  // Plan and execute:

  target_pose2 = target_pose1;


  move_group.move();




//  moveit::planning_interface::MoveGroupInterface::Plan my_plan;
//  bool success = (move_group.plan(my_plan) == moveit::planning_interface::MoveItErrorCode::SUCCESS);
  //if (contact == true){
  //  move_group.stop();
  //}
  //ROS_INFO_NAMED("tutorial", "Visualizing plan 1 (pose goal) %s", success ? "" : "FAILED");
  //ROS_INFO_NAMED("tutorial", "Visualizing plan 1 as trajectory line");

//visual_tools.publishText(text_pose, "Pose Goal", rvt::WHITE, rvt::XLARGE);
//  visual_tools.publishTrajectoryLine(my_plan.trajectory_, joint_model_group);
  //visual_tools.trigger();

    }

  loop_rate.sleep();
  }
  ros::shutdown();
  return 0;
}

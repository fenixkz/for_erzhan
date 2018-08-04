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

int main(int argc, char **argv)
{
  ros::init(argc, argv, "xy");
  ros::AsyncSpinner spinner(0);
  spinner.start();
  ros::NodeHandle pub;
  ros::NodeHandle pub1;
  ros::Publisher xdata = pub.advertise<std_msgs::Float64>("/x_coord", 100);
  ros::Publisher ydata = pub1.advertise<std_msgs::Float64>("/y_coord", 100);
  static const std::string PLANNING_GROUP = "arm";
  moveit::planning_interface::MoveGroupInterface move_group(PLANNING_GROUP);
  moveit::planning_interface::PlanningSceneInterface planning_scene_interface;
  const robot_state::JointModelGroup *joint_model_group =
      move_group.getCurrentState()->getJointModelGroup(PLANNING_GROUP);
      std_msgs::Float64 x_coord;
      std_msgs::Float64 y_coord;
      geometry_msgs::PoseStamped target_pose1;
      ros::Rate loop_rate(50);
      while (ros::ok()){
        target_pose1 = move_group.getCurrentPose();
        x_coord.data = target_pose1.pose.position.x;
        y_coord.data = target_pose1.pose.position.y;
        xdata.publish(x_coord);
        ydata.publish(y_coord);
        ros::spinOnce();
        loop_rate.sleep();
        }
        ros::shutdown();
        return 0;
      }

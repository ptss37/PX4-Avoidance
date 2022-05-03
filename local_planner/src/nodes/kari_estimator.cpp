#include "ros/ros.h"
#include "std_msgs/String.h"
#include "geometry_msgs/PoseStamped.h"

#include <sstream>

void positionCallback(const geometry_msgs::PoseStamped& msg) {
  ROS_INFO("I heard: [%f]", msg.pose.position.x);
}


/**
 * This tutorial demonstrates simple sending of messages over the ROS system.
 */
int main(int argc, char **argv)
{
  /**
   * The ros::init() function needs to see argc and argv so that it can perform
   * any ROS arguments and name remapping that were provided at the command line.
   * For programmatic remappings you can use a different version of init() which takes
   * remappings directly, but for most command-line programs, passing argc and argv is
   * the easiest way to do it.  The third argument to init() is the name of the node.
   *
   * You must call one of the versions of ros::init() before using any other
   * part of the ROS system.
   */
  ros::init(argc, argv, "kari_estimator");

  /**
   * NodeHandle is the main access point to communications with the ROS system.
   * The first NodeHandle constructed will fully initialize this node, and the last
   * NodeHandle destructed will close down the node.
   */
  ros::NodeHandle n;

  /**
   * The advertise() function is how you tell ROS that you want to
   * publish on a given topic name. This invokes a call to the ROS
   * master node, which keeps a registry of who is publishing and who
   * is subscribing. After this advertise() call is made, the master
   * node will notify anyone who is trying to subscribe to this topic name,
   * and they will in turn negotiate a peer-to-peer connection with this
   * node.  advertise() returns a Publisher object which allows you to
   * publish messages on that topic through a call to publish().  Once
   * all copies of the returned Publisher object are destroyed, the topic
   * will be automatically unadvertised.
   *
   * The second parameter to advertise() is the size of the message queue
   * used for publishing messages.  If messages are published more quickly
   * than we can send them, the number here specifies how many messages to
   * buffer up before throwing some away.
   */
  ros::Publisher chatter_pub = n.advertise<std_msgs::String>("chatter", 1000);
  ros::Subscriber sub = n.subscribe("/mavros/local_position/pose", 1000, positionCallback);

  // velocity_sub_ = n.subscribe<const geometry_msgs::TwistStamped&>("/mavros/local_position/velocity_local", 1,
  //                                                                   &LocalPlannerNodelet::velocityCallback, this);
  // state_sub_ = n.subscribe("/mavros/state", 1, &LocalPlannerNodelet::stateCallback, this);
  // clicked_point_sub_ = n.subscribe("/clicked_point", 1, &LocalPlannerNodelet::clickedPointCallback, this);
  // clicked_goal_sub_ = n.subscribe("/move_base_simple/goal", 1, &LocalPlannerNodelet::clickedGoalCallback, this);
  // fcu_input_sub_ = n.subscribe("/mavros/trajectory/desired", 1, &LocalPlannerNodelet::fcuInputGoalCallback, this);
  // goal_topic_sub_ = n.subscribe("/input/goal_position", 1, &LocalPlannerNodelet::updateGoalCallback, this);
  // distance_sensor_sub_ = n.subscribe("/mavros/altitude", 1, &LocalPlannerNodelet::distanceSensorCallback, this);
  // mavros_vel_setpoint_pub_ = n.advertise<geometry_msgs::Twist>("/mavros/setpoint_velocity/cmd_vel_unstamped", 10);
  // mavros_pos_setpoint_pub_ = n.advertise<geometry_msgs::PoseStamped>("/mavros/setpoint_position/local", 10);
  // mavros_obstacle_free_path_pub_ = n.advertise<mavros_msgs::Trajectory>("/mavros/trajectory/generated", 10);
  // mavros_obstacle_distance_pub_ = n.advertise<sensor_msgs::LaserScan>("/mavros/obstacle/send", 10);



  ros::Rate loop_rate(10);

  /**
   * A count of how many messages we have sent. This is used to create
   * a unique string for each message.
   */
  int count = 0;
  while (ros::ok())
  {
    /**
     * This is a message object. You stuff it with data, and then publish it.
     */
    std_msgs::String msg;

    std::stringstream ss;
    ss << "hello world " << count;
    msg.data = ss.str();

    ROS_INFO("%s", msg.data.c_str());

    /**
     * The publish() function is how you send messages. The parameter
     * is the message object. The type of this object must agree with the type
     * given as a template parameter to the advertise<>() call, as was done
     * in the constructor above.
     */
    chatter_pub.publish(msg);

    ros::spinOnce();

    loop_rate.sleep();
    ++count;
  }


  return 0;
}
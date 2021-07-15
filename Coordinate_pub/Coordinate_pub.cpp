#include <Coordinate_pub/Coordinate_pub.hpp>

namespace coordinate_pub{



  Co_Pub::Co_Pub(void){
    count =0;
    FLAG_EVENT = false;
    FLAG_ERASE = false;
    ros::NodeHandle private_nh("~");
    private_nh.param("file_name_", file_name_ , std::string("/home/robo/catkin_ws/src/Coordinate_pub/task_point.csv"));
    std::cout<<"オブジェクト生成"<<std::endl;
    file_.open(file_name_,std::ios::trunc);
    file_ <<"NO."<<","<< Co_Pub::mode_ <<"x"<<","<<"y"<<","<<"z"<<","<<"ox"<<","<<"oy"<<","<<"oz"<<","<<"w" << std::endl;
    file_.close();
  }

  Co_Pub::~Co_Pub(void){

  }

  void Co_Pub::run(void){
    ros::NodeHandle nh;
    Co_Pub::Co_sub_ = nh.subscribe("mode_publisher/mode",1,&Co_Pub::get,this);
    // while(ros::ok()){
      // std::cout<<"待機中"<<std::endl;
      ros::Rate rate(10);
      ros::spinOnce();
      rate.sleep();
    // }
  }

  void Co_Pub::get(const std_msgs::String::ConstPtr& mode){
    std::cout<<"座標取得中"<<std::endl;
    ros::Rate rate(10);
    Co_Pub::mode_ = mode->data;
    while (ros::ok()){
     try{
       listener_.lookupTransform("/map", "/base_link", ros::Time(0), transform_);
     }
     catch (tf::TransformException ex){
       ROS_ERROR("%s",ex.what());
       ros::Duration(1.0).sleep();
     }
     break;
    }
    FLAG_EVENT = true;
   }

  void Co_Pub::IN_POINT(double x,double y,double z,double ox,double oy,double oz,double ow,int waypoint_count){
    POINT_x=x;
    POINT_y=y;
    POINT_z=z;
    POINT_ox=ox;
    POINT_oy=oy;
    POINT_oz=oz;
    POINT_ow=ow;
    way_count=waypoint_count;
    Co_Pub::output();
  }

  bool Co_Pub::event_flag(){
    return FLAG_EVENT;
  }

  bool Co_Pub::erase_flag(double diff_way ,double diff_yaw ,int w_count){
    if(w_count!=1&&((diff_yaw * 180.0 / M_PI >10 && diff_way <3) ||diff_way <0.1)){
      FLAG_ERASE=true;
    }
    return FLAG_ERASE;
  }

  void Co_Pub::event_flag_to_false(){
    FLAG_EVENT = false;
    FLAG_ERASE = false;
  }

  void Co_Pub::output(){
    file_.open(file_name_,std::ios::app);
    if (!file_){
      std::cout << "ファイルが開けませんでした。" << std::endl;
      std::cin.get();
    }
    std::cout<<"タスクポイント出力"<<std::endl;
    file_ << way_count<<","<<Co_Pub::mode_ <<","<<POINT_x<<","<<POINT_y<<","<<POINT_z<<","<<POINT_ox<<","<<POINT_oy<<","<<POINT_oz<<","<<POINT_ow << std::endl;
    std::cout<< way_count<<","<<Co_Pub::mode_ <<","<<POINT_x<<","<<POINT_y<<","<<POINT_z<<","<<POINT_ox<<","<<POINT_oy<<","<<POINT_oz<<","<<POINT_ow << std::endl;
    file_.close();
  }

};

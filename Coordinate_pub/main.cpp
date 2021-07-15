#include "stdafx.hpp"
#include <Coordinate_pub/Coordinate_pub.hpp>


int main(int argc, char **argv)
{
	// ROSの初期化
	ros::init(argc, argv, "Coordinate_pub");

	//タスクポイントの受け取り
	coordinate_pub::Co_Pub co;
	co.run();
	return 0;
}

#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include<opencv2/calib3d.hpp>//要用getPerspectiveTransform需要包含此头文件
#include <iostream>

using namespace cv;
using namespace std;


//////////变换图像///////////
//右键图片，画图模式看坐标
float w = 250, h = 350;//卡片尺寸
Mat imgWarp1,imgWarp2;//定义矩阵

void main() {
	string path = "Resources/cards.jpg";
	Mat img = imread(path);
//定义源点	
	Point2f src1[4] = { {529,142},{771,190},{405,395},{674,457} };
	Point2f src2[4] = { {776,107},{1017,83},{840,360},{1119,333} };
//明确变换点	
	Point2f dst1[4] = { {0.0f,0.0f},{w,0.0f},{0.0f,h},{w,h} };
	Point2f dst2[4] = { {0.0f,0.0f},{w,0.0f},{0.0f,h},{w,h} };
	Mat matrix1 = getPerspectiveTransform(src1, dst1);
	Mat matrix2 = getPerspectiveTransform(src2, dst2);
//变换图像
	warpPerspective(img, imgWarp1, matrix1,Point(w,h));
	warpPerspective(img, imgWarp2, matrix2, Point(w, h));
//创建圆明确点位
	for (int i = 0; i < 4; i++) {
		circle(img, src1[i], 10, Scalar(0, 0, 255),FILLED);
		circle(img, src2[i], 10, Scalar(0, 0, 255),FILLED);
	}
	
	imshow("Image", img);
	imshow("Image Warp1", imgWarp1);
	imshow("Image Warp2", imgWarp2);
	waitKey(0);
}

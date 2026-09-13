#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include<opencv2/calib3d.hpp>//要用getPerspectiveTransform需要包含此头文件
#include <iostream>

using namespace cv;
using namespace std;


//////////颜色检测///////////
void main() {
	string path = "Resources/lambo.png";
	Mat img = imread(path);
	Mat imgHSV,mask;
	int hmin = 0, smin = 110, vmin = 153;
	int hmax = 19, smax = 240, vmax = 255;
//如何找到目标颜色值
//opencv内置颜色值滑块
	//创建滑块窗口与滑轨
	namedWindow("Trackbars", (640, 200));
	createTrackbar("Hue Min", "Trackbars", &hmin, 179);//色相最大值即179
	createTrackbar("Hue Max", "Trackbars", &hmax, 179);
	createTrackbar("Sat Min", "Trackbars", &smin, 255);
	createTrackbar("Sat Max", "Trackbars", &smax, 255);
	createTrackbar("Val Min", "Trackbars", &vmin, 255);
	createTrackbar("Val Max", "Trackbars", &vmax, 255);
	
	
//转HSV空间（可以了解更多色彩信息）
	cvtColor(img, imgHSV, COLOR_BGR2HSV);

//提取色彩
	while (true) {
		Scalar lower(hmin, smin, vmin);//设置下限
		Scalar upper(hmax, smax, vmax);//设置上限
		inRange(imgHSV, lower, upper, mask);//mask做掩码，提取橙色

		imshow("Image", img);
		imshow("Image HSV", imgHSV);
		imshow("Image Mask", mask);
		waitKey(1);
	}
}

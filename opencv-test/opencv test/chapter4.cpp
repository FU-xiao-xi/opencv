#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;


////////////绘制形状///////////
void main() {
//空白图像
	Mat img(512,512,CV_8UC3,Scalar(175,180,90));
//圆形	
	circle(img, Point(256, 256), 155, Scalar(0, 69, 255),100);
//矩形
	rectangle(img, Point(130, 226), Point(382, 286), Scalar(255, 255, 255), 3);//两点定位
//线
	line(img, Point(130, 300), Point(382, 369), Scalar(255,255,255),2);
///////////放置文本/////////////
	putText(img, "Tan's Workshop", Point(137, 262), FONT_HERSHEY_COMPLEX, 0.75, Scalar(189, 56, 77), 2);
	
	imshow("Image", img); 

	waitKey(0);
}
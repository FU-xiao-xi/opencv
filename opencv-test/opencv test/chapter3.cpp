#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;
void main() {
	string path = "Resources/test.png";
	Mat img = imread(path);
	Mat imgResize,imgCrop;
//调整图像大小//
	//cout << img.size() << endl; // 
	//确认原图像大小
	resize(img, imgResize, Size(),0.5,0.5);
	//Size像素放缩，double x double y比例放缩
//裁剪图像//
	Rect roi(200, 100, 300, 300);//坐标，宽度和高度
	imgCrop = img(roi);
	imshow("Image", img);
	imshow("Image Resize", imgResize);
	imshow("Image Crop", imgCrop);
	waitKey(0);
}
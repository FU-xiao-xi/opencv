#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;


//////////基本功能///////////
void main() {
	string path = "Resources/test.png";
	Mat img = imread(path);
	Mat imgGray,imgBlur,imgCanny,imgDil,imgErode;
	//转灰度图像//
	cvtColor(img, imgGray, COLOR_BGR2GRAY);
	//加模糊效果//
	GaussianBlur(imgGray, imgBlur, Size(9, 9), 0, 0);
	//边缘检测//
	Canny(imgBlur, imgCanny, 10,150 );
	//图像膨胀//
	Mat kernel = getStructuringElement(MORPH_RECT, Size(5, 5));
	dilate(imgCanny, imgDil,kernel);
	//图像腐蚀//
	erode(imgDil, imgErode, kernel);
	imshow("Image", img); 
	imshow("Image Gray", imgGray);
	imshow("Image Blur", imgBlur);
	imshow("Image Canny", imgCanny);
	imshow("Image Dilation", imgDil);
	imshow("Image Erode", imgErode);

	waitKey(0);
}

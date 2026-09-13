#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include<opencv2/calib3d.hpp>//本章节好多函数名也需要用到这个
#include <iostream>

using namespace cv;
using namespace std;

//需用新函数 轮廓检索
void getContours(Mat imgDil,Mat img) {
	//contours是向量，最终单位是坐标
	vector<vector<Point>> contours;
	//双重 一个图中有多个图像，一个图像又有多个点
	vector<Vec4i> hierarchy;
	//4i有四个整数值表示这一个向量，存放轮廓的层级关系
	findContours(imgDil,contours,hierarchy,RETR_EXTERNAL,CHAIN_APPROX_SIMPLE);
	//RETR_EXTERNAL 只找最外层轮廓 
	// CHAIN_APPROX_SIMPLE 压缩轮廓点，比如直线只存两端
	/*drawContours(img, contours, -1, Scalar(255, 0, 255), 2, 2);*///画出轮廓
	
	vector<vector<Point>> conPoly(contours.size());
	//定义容器存放简化版轮廓(点)
	vector<Rect>boundRect(contours.size());
	string objectType;
	//面积过滤 循环遍历先找到所有图像面积
	for (int i = 0;i < contours.size();i++) {
		//contours,size相当于一个容器，如有3个图形，则其为3
		int area =contourArea(contours[i]);
		cout<<area<<endl;//打印面积 从而判断忽略掉的噪声范围
		
		
		if (area > 1000) {
			float peri = arcLength(contours[i],true);
			//计算轮廓周长，true表示轮廓闭合
			//多边形逼近 0.02*peri表示某个点到直线距离小于2%则可合并 值小精细
			approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);//输入 输出 参数 轮廓闭合
			
			//判断顶点个数从而识别形状
			cout << conPoly[i].size() << endl;
			boundRect[i] = boundingRect(conPoly[i]);
			
			//定义容器储存角点数并根据数量判断形状
			int objCor = (int)conPoly[i].size();
			if (objCor == 3) { objectType = "Tri"; };
			if (objCor == 4) {
				float aspRatio = (float)boundRect[i].width / (float)boundRect[i].height;
				if (aspRatio > 0.95 && aspRatio < 1.05) { objectType = "Square"; }
				else { objectType = "Rect";}
			}
			if (objCor > 4) { objectType = "Circle"; };
			drawContours(img, conPoly, i, Scalar(0, 0, 255), 3, 2);//画出轮廓（-1表示画出所有）
			rectangle(img,boundRect[i].tl(), boundRect[i].br(), Scalar(255, 255, 0), 1);//两点定位 topleft bottomright 画出矩形边界
			putText(img,objectType, {boundRect[i].x,boundRect[i].y-5}, FONT_HERSHEY_PLAIN,1, Scalar(189, 56, 77), 1);

		}

	}

}
//////////形状检测///////////  
void main() {
//预处理  先找到边缘
	string path = "Resources/shapes.png";
	Mat img = imread(path);
	Mat imgGray, imgBlur, imgCanny, imgDil;
	//转灰度图像//
	cvtColor(img, imgGray, COLOR_BGR2GRAY);
	//加模糊效果//
	GaussianBlur(imgGray, imgBlur, Size(3, 3), 0, 0);
	//边缘检测//数值越低画的线越多，Canny依靠灰度对比检测边缘，故要先转灰度图像，模糊越大会使边缘检测越不敏感
	Canny(imgBlur, imgCanny, 5, 150);
	//图像膨胀// 可使边缘线更实
	Mat kernel = getStructuringElement(MORPH_RECT, Size(9, 9));
	dilate(imgCanny, imgDil, kernel);
	//调用所定义的函数
	getContours(imgDil, img);//检索轮廓及画出轮廓的两张图像
	imshow("Image", img); 
	/*imshow("Image Gray", imgGray);
	imshow("Image Blur", imgBlur);
	imshow("Image Canny", imgCanny);
	imshow("Image Dilation", imgDil);*/
	waitKey(0);
}


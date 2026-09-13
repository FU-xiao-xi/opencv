#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;


////////////如何调用图片///////////
//void main() {
//	string path = "Resources/test.png";
//	Mat img = imread(path);
// if (img.empty()){
//     cout<<"图片读取失败！检查路径"<<endl;
//     return -1;
// }
// 
//	imshow("Image", img); 
//	waitKey(0);
//}

/////////////如何调用视频////////////
//void main() {
//	string path = "Resources/test_video.mp4";
//	VideoCapture cap(path);
//	Mat img ;
//	while (true) {
//		cap.read(img);
//		imshow("Image", img);
//		waitKey(20);
//	}
//	
//}

//////////////如何开启摄像头////////////
//void main() {
//	
//	VideoCapture cap(0);
//	Mat img;
//	while (true) {
//		cap.read(img);
//		imshow("Image", img);
//		waitKey(20);
//	}

}



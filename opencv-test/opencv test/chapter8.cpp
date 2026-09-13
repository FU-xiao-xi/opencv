#include <opencv2/opencv.hpp>
#include <iostream>
//由于下载了opencv5.0版本，objdetect中无CascadeClassifier，故换成FaceDetectorYN
using namespace cv;
using namespace std;


//////////如何调用图片///////////
int main() {
	string path = "Resources/group_photo.jpg";//识别军训大合照人脸
	Mat img = imread(path);
	if (img.empty()) {
		     cout<<"图片读取失败！检查路径"<<endl;
		     return -1;
		 }
	/*CascadeClassifier faceCascade;*/
	//加载YuNet模型
    string modelPath = "D:\\vs2026daima\\opencv test\\Resources\\face_detection_yunet_2023mar.onnx";
    //Ptropencv自定义的智能指针
    Ptr<FaceDetectorYN> detector = FaceDetectorYN::create(
        modelPath,
        "",                // 配置文件（YuNet 不需要，留空）
        Size(0,0),    // 模型输入尺寸，把原图放到此尺寸后才开始检测
        0.9f,              // 置信度阈值（大于0.9才认为是人脸）
        0.3f,              // NMS 阈值
        5000               // 最多检测多少张脸
    );
    //让程序检测原图多大
    detector->setInputSize(img.size());

    Mat faces;
    detector->detect(img, faces);//->是指针调用的方法
    cout << "faces行数：" << faces.rows << " 列数：" << faces.cols << endl;
    // 判断一下，只有当检测到人脸（列数 > 0）且矩阵里有足够数据时才画框
    if (faces.rows > 0 && faces.cols > 0) {
        for (int i = 0;i < faces.rows;i++) {
            if (faces.at<float>(i, 0) == 0 && faces.at<float>(i, 1) == 0) continue;
            Rect box(
                (int)faces.at<float>(i, 0),
                (int)faces.at<float>(i, 1),
                (int)faces.at<float>(i, 2),
                (int)faces.at<float>(i, 3)
            );
            rectangle(img, box, Scalar(0, 255, 0), 3);;
            rectangle(img, box, Scalar(255, 0, 255), 1);
        }
    }
    // 先判断一下是不是假脸 空矩阵也会显示1
    if (faces.rows > 0 && faces.at<float>(0, 0) == 0) {
        cout << "检测到 0 张人脸（模型返回了空矩阵）" << endl;
    }
    else {
        cout << "检测到 " << faces.rows << " 张人脸" << endl;
    }
    
    //resize(img, imgSmall, Size(1500, 150)）;//原图太大显示不全，故改显示尺寸，但效果不佳
    
    Rect roi1(0, 0, img.cols/2, img.rows);  // 裁剪左半
    Mat leftPart = img(roi1);          // 取出左半部分
    Rect roi2(img.cols/2, 0, img.cols/2, img.rows);  
    Mat rightPart = img(roi2);
    namedWindow("Left Part", WINDOW_GUI_NORMAL);//自由放缩窗口比例，但效果不佳
    namedWindow("Right Part", WINDOW_GUI_NORMAL);
    namedWindow("Image", WINDOW_GUI_NORMAL);
    imshow("Left Part", leftPart);
    imshow("Right Part",rightPart);
	imshow("Image", img); 
	waitKey(0);
}
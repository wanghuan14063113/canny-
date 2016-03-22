#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int edgeThresh = 3;
// 声明 原始图片，灰度图片，和 canny边缘图片
Mat image, cedge;
Mat gray, edge;
void onTrackbar(int, void*)
{
	//blur 灰度图片
	blur(gray, edge, Size(3, 3));
	// Canny 边缘检测
	Canny(gray, edge, edgeThresh, edgeThresh * 3, 3);
	//全部设为0
	cedge = Scalar::all(0);
	//拷贝边缘的象素点
	image.copyTo(cedge, edge);
	imshow("Edge map", cedge);
}
int main()//
{
	//从文件中读入图像
	image = imread("C:\\Users\\Administrator\\Desktop\\mydataset\\2344.jpg");
	//如果读入图像失败
	if (image.empty())
	{
		fprintf(stderr, "Can not load image\n");
		return -1;
	}
	// 生成灰度图片，因为只有灰度图片才能生成边缘图片
	cedge.create(image.size(), image.type());
	cvtColor(image, gray, CV_BGR2GRAY);
	//新建一个窗口
	namedWindow("Edge map", 1);
	// 生成一个进度条来控制边缘检测
	createTrackbar("Canny Threshold", "Edge map", &edgeThresh, 100, onTrackbar);
	//初始化图像
	onTrackbar(0, 0);
	//此函数等待按键，按键盘任意键就返回
	waitKey();
	return 0;
}

// opencvdome.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include <iostream> 
#include <fstream>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp> 
#include<opencv2/highgui/highgui.hpp> 
#include <opencv2/imgproc/imgproc.hpp>
#include <math.h>
using namespace cv;
using namespace std;
int main()
{
	//载入原始图，且必须以二值图模式载入
	Mat M = imread("C:\\Users\\liaobh\\Desktop\\廖斌华\\1.png", 0);
	imshow("原始图", M);

	waitKey(500); //等待5000ms后窗口自动关闭
	//初始化结果图
	Mat dstImage = Mat::zeros(M.rows, M.cols, CV_8UC3);
	imshow("dstimage",dstImage );
	//M提取阈值小于250的部分
	M = M < 250;
	imshow("阈值", M);
	waitKey(50);
	//定义轮廓和层次结构
	vector<vector<Point>>contours;
	vector<Vec4i>hierarchy;
	findContours(M, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_NONE);
	//迭代器输出
	/*for (vector<vector<Point>>::iterator it=contours.begin();it!=contours.end();++it)
	{
		for (vector<Point>::iterator inner_it=it->begin();inner_it!=it->end();++inner_it)
		{
			cout<<*inner_it<<endl;
		}
	}
*/
//下标输出
	for (int i = 0; i < contours.size(); i++)
	{
		for (int j = 0; j < contours[i].size(); j++)
		{
			cout << contours[i][j].x << "   " << contours[i][j].y << endl;
			ofstream f;
			f.open("E:/坐标轮廓线.txt", ios::out | ios::app);
			f << contours[i][j].x << "  " << contours[i][j].y << endl;
		}
	}

	//遍历顶层轮廓，以随机颜色绘制出每个连接组件颜色
	int index = 0;
	for (; index >= 0; index = hierarchy[index][0])
	{
		Scalar color(rand() % 255, rand() % 255, rand() % 255);
		drawContours(dstImage, contours, index, color, 1, 8, hierarchy);
	}

	imshow("轮廓图", dstImage);
	waitKey(5000); //等待5000ms后窗口自动关闭
	getchar();
}
// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件

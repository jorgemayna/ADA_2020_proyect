// opencvAplication.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

#include "matching1.h"
#include <iostream>

using namespace cv;
using namespace std;

void matching() {
	string a, b;
	marcador();
	cout << "a = ";
	cin >> a;
	cout << "b = ";
	cin >> b;

	auto A = bloques_final(a, 9);
	auto B = bloques_final(b, 9);

	cout << endl;
	cout << "A = ";
	print_1(A);
	cout << "B = ";
	print_1(B);
	cout << endl;

	//auto match = greedy(A,B);
	//auto match = recursivo(A,B);
	//auto match = memoizado(A,B);
	auto match = p_dinamica(A, B);
	print_matching(match);
}

void prueba(Mat imagen1, Mat imagen2, Mat imagen1_bin, Mat imagen2_bin) {
	auto A = bloques_opencv(imagen1_bin, 0, imagen1_bin.size().width);
	auto B = bloques_opencv(imagen2_bin,0, imagen2_bin.size().width);

	cout << endl;
	cout << "A = ";
	print_1(A);
	cout << "B = ";
	print_1(B);
	cout << endl;

	auto match = p_dinamica(A, B);
	print_matching(match);


	for (int i = 0; i < A.size(); i++) {

	}

	imshow("Display window", imagen1_bin);
	waitKey(0);
	imshow("Display window", imagen2_bin);
	waitKey(0);
}

int main(){
	
	
	
	string file = "elena.jpg";
	Mat image = imread(file, IMREAD_COLOR); // IMREAD_COLOR
	Mat image_gray,image_binary;
	cvtColor(image, image_gray, COLOR_BGR2GRAY);

	string file2 = "bella.jpg";
	Mat image2 = imread(file2, IMREAD_COLOR); // IMREAD_COLOR
	Mat image2_gray, image2_binary;
	cvtColor(image2, image2_gray, COLOR_BGR2GRAY);

	if (image.empty())
	{
		std::cout << "Could not read the image: " << file << std::endl;
		return 1;
	}
	if (image2.empty())
	{
		std::cout << "Could not read the image: " << file2 << std::endl;
		return 1;
	}

	cout << "width" << image.size().width << endl;
	cout << "height" << image.size().height << endl;
	
	/*
	for (int z = 0; z < 100; z++) {
		imshow("Display window", image);
		
		waitKey(100);
		for (int i = 0; i < image.size().width; i++) {
			image.at<cv::Vec3b>(z, i)[0] = 0;
			image.at<cv::Vec3b>(z, i)[1] = 0;
			image.at<cv::Vec3b>(z, i)[2] = 0;
		}

	}
	*/
	threshold(image_gray, image_binary, 100, 255, THRESH_BINARY_INV);
	threshold(image2_gray, image2_binary, 100, 255, THRESH_BINARY_INV);

	//prueba(image,image2,image_binary, image2_binary);
	
	imshow("Display window", image);	
	waitKey(0);

	imshow("Display window", image2);
	waitKey(0);

	imshow("Display window", image_gray);
	waitKey(0);

	imshow("Display window", image2_gray);
	waitKey(0);

	imshow("Display window", image_binary);
	waitKey(0);

	imshow("Display window", image2_binary);
	waitKey(0);

	for (int j = 0; j < image.size().height; j++) {
		for (int i = 0; i < image.size().height; i++) {
			image.at<cv::Vec3b>(j, i)[0] = image2.at<cv::Vec3b>(j, i)[0];
			image.at<cv::Vec3b>(j, i)[1] = image2.at<cv::Vec3b>(j, i)[1];
			image.at<cv::Vec3b>(j, i)[2] = image2.at<cv::Vec3b>(j, i)[2];
			if (i % 200 == 0) {
				imshow("Display window", image);
				waitKey(2);
			}			
		}
	}

	imshow("Display window", image);
	waitKey(0);

	

	/*
	imshow("Display window", image);
	matching();
	waitKey(0);

	imshow("Display window", image_gray);
	waitKey(0);

	threshold(image_gray, image_binary, 100, 255, THRESH_BINARY_INV);
	imshow("Display window", image_binary);

	Scalar gg =image_binary.at<uchar>(110, 100);
	cout <<"\nbit: " <<  gg.val[0];

	int k = waitKey(0);

	if (k == 's')
	{		
		imwrite("pajaro.jpg", image);
	}
	*/
	

	return 0;

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

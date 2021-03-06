


#include "stdafx.h"
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

const string WindowName = "Face Detection example";

int main(int, char**)
{
	namedWindow(WindowName);

	
	string cascadefilename = "haarcascade_frontalface_default.xml";
	CascadeClassifier cascade;
	cascade.load(cascadefilename);
	string cascadefilenameeye = "haarcascade_eye.xml";
	CascadeClassifier cascadeye;
	cascadeye.load(cascadefilenameeye);

	if (cascade.empty()) {
		printf("Error: Cannot load");
		return 2;
	}
	if (cascadeye.empty()) {
		printf("Error: Cannot load");
		return 2;
	}
	VideoCapture cap(0);
	if (!cap.isOpened()){  
		return -1;
	}
	int x = 5;
	
	Vec3b color;
	color.val[0] = 0;
	color.val[1] = 255;
	color.val[2] = 255;
	Vec3b color2;
	color2.val[0] = 255;
	color2.val[1] = 0;
	color2.val[2] = 255;
	Mat Gray;
	vector<Rect> Faces;
	vector<Rect> eyes;
	Mat img;

	while(1){
		cap >> img;
		if (img.empty()) {
			break;
		}
		cvtColor(img, Gray, COLOR_BGR2GRAY);
		
		cascade.detectMultiScale(Gray, Faces, 1.3, 5);
	
		for (int i = 0; i < Faces.size(); i++) {
			rectangle(img, Faces[i], color);
		}
		cascadeye.detectMultiScale(Gray, eyes, 1.3, 5);
		for (int i = 0; i < eyes.size(); i++) {
			rectangle(img, eyes[i], color2);
		}
		imshow(WindowName, img);
		if (waitKey(1) == 27) {
			break;
		}
	
	}

	cap.release();

	return 0;
}


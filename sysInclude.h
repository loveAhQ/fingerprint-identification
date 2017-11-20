#pragma once
//openCV head file
#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc/imgproc.hpp> 
#include <opencv2/highgui/highgui.hpp>

//c++ head file
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

//the tool class used for debug
class CTool
{
public:

	//show image using OpenCV
	//tMat = a image
	static void ShowImage(cv::Mat & tMat);

	//wait a input using OpenCV
	static void WaitCV();

	//wait a input using console system
	static void Wait();

	//report the errors using console system
	//content = the error
	static void Error(char* error);

	//reportthe error using a text file
	static void ErrorFile(char* error);

private:
	static int index; //the OpenCV window index

};


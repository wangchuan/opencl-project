#ifndef ALGORITHM_H_
#define ALGORITHM_H_

#include "CLApp.h"
#include <opencv/cv.h>
#include <opencv2/opencv.hpp>

class Algorithm
{
public:
	Algorithm();
	~Algorithm();

	void						InitCLApp(CLApp* CLAppObj, const std::string& CLSrcFilePath);
	void						ExecuteCLApp1(CLApp* CLAppObj);
	void						ExecuteCLApp2(CLApp* CLAppObj);
	void						ExecuteCLApp3(CLApp* CLAppObj);
};

#endif
#ifndef ALGORITHM_H_
#define ALGORITHM_H_

#include "CLApp.h"

class Algorithm
{
public:
	Algorithm();
	~Algorithm();

	void						InitCLApp(CLApp* CLAppObj, const std::string& CLSrcFilePath);
	void						ExecuteCLApp1(CLApp* CLAppObj);
	void						ExecuteCLApp2(CLApp* CLAppObj);
};

#endif
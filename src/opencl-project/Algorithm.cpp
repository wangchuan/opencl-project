#include "Algorithm.h"

using namespace std;

Algorithm::Algorithm()
{

}

Algorithm::~Algorithm()
{

}

void Algorithm::InitCLApp(CLApp* CLAppObj, const std::string& CLSrcFilePath)
{
	vector<string> KernelNames;
	KernelNames.push_back("simple_add");
	KernelNames.push_back("hello");
	KernelNames.push_back("image_process");
	CLAppObj->Init(CLSrcFilePath, KernelNames);
}

void Algorithm::ExecuteCLApp1(CLApp* CLAppObj)
{
	int A[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	int B[] = { 0, 1, 2, 0, 1, 2, 0, 1, 2, 0 };
	int C[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	int n = sizeof(A) / sizeof(int);
	cl::CommandQueue cmdQueue = CLAppObj->GetCmdQueue();
	CLBuffer bufA = CLAppObj->CreateBuffer(A, sizeof(A), CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR);
	CLBuffer bufB = CLAppObj->CreateBuffer(B, sizeof(B), CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR);
	CLBuffer bufC = CLAppObj->CreateBuffer(C, sizeof(C), CL_MEM_WRITE_ONLY | CL_MEM_USE_HOST_PTR);
	cl::Kernel& kernel = CLAppObj->GetKernel("simple_add");
	kernel.setArg(0, bufA.first);
	kernel.setArg(1, bufB.first);
	kernel.setArg(2, bufC.first);
	cmdQueue.enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(n), cl::NullRange);
	cmdQueue.finish();

	cmdQueue.enqueueReadBuffer(bufC.first, CL_TRUE, 0, sizeof(C), C);
	cout << "Result: " << endl;
	for (int i = 0; i < n; i++)
		cout << C[i] << " ";
}

void Algorithm::ExecuteCLApp2(CLApp* CLAppObj)
{
	cl::CommandQueue cmdQueue = CLAppObj->GetCmdQueue();
	char A[256] = { 0 };
	CLBuffer buf = CLAppObj->CreateBuffer(A, sizeof(A), CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR);
	cl::Kernel& kernel = CLAppObj->GetKernel("hello");
	kernel.setArg(0, buf.first);
	cmdQueue.enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(256), cl::NullRange);
	cmdQueue.finish();

	cmdQueue.enqueueReadBuffer(buf.first, CL_TRUE, 0, sizeof(A), A);
	cout << A;
}

void Algorithm::ExecuteCLApp3(CLApp* CLAppObj)
{
	cv::Mat I = cv::imread("test.png", CV_LOAD_IMAGE_GRAYSCALE);
	cv::Mat Iorig = I.clone();
	cl::CommandQueue cmdQueue = CLAppObj->GetCmdQueue();
	CLBuffer buf = CLAppObj->CreateBuffer(I.data, I.total(), CL_MEM_READ_WRITE | CL_MEM_USE_HOST_PTR);
	cl::Kernel& kernel = CLAppObj->GetKernel("image_process");
	kernel.setArg(0, buf.first);
	kernel.setArg(1, I.rows);
	kernel.setArg(2, I.cols);
	cmdQueue.enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(I.rows, I.cols), cl::NullRange);
	cmdQueue.finish();
	cmdQueue.enqueueReadBuffer(buf.first, CL_TRUE, 0, I.total(), I.data);
	cv::imshow("IOrig", Iorig);
	cv::imshow("I", I);
	cv::waitKey(0);
}

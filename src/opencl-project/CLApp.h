#ifndef CLAPP_H_
#define CLAPP_H_

#define CL_USE_DEPRECATED_OPENCL_1_1_APIS

#if defined(__APPLE__) || defined(__MACOSX)
#include <OpenCL/cl.hpp>
#else
#include <CL/cl.hpp>
#include <CL/opencl.h>
#endif

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <unordered_map>

typedef std::pair<cl::Buffer, int> CLBuffer;

class CLApp
{
public:
	CLApp();
	~CLApp();

	void											Init(const std::string& src, const std::vector<std::string>& kernel_names);
	inline cl::CommandQueue							GetCmdQueue() const { return mCmdQueue; }
	inline cl::Kernel&								GetKernel(const std::string& kernel_name) { return mKernelDict.at(kernel_name); }
	CLBuffer										CreateBuffer(void* dataptr, size_t datasize, int flag);

private:
	std::vector<cl::Platform>						mPlatforms;
	std::vector<cl::Device>							mDevices;
	cl::Context										mContext;
	cl::CommandQueue								mCmdQueue;
	cl::Program										mProgram;
	std::unordered_map<std::string, cl::Kernel>		mKernelDict;
	std::string										mSrcFile;
};

#endif
#define __CL_ENABLE_EXCEPTIONS
#include "CLApp.h"

using namespace std;

std::string load_cl_source_file(std::string input)
{
	std::ifstream stream(input.c_str());
	if (!stream.is_open()) 
	{
		cout << " No *.cl file found!" << endl;
		exit(1);
	}
	return std::string(std::istreambuf_iterator<char>(stream),
		(std::istreambuf_iterator<char>()));
}

CLApp::CLApp()
{
	cl::Platform::get(&mPlatforms);
	if (mPlatforms.empty())
	{
		cout << " No platforms found. Check OpenCL installation!" << endl;
		exit(1);
	}
	cl::Platform default_platform = mPlatforms[0];
	default_platform.getDevices(CL_DEVICE_TYPE_ALL, &mDevices);
	if (mDevices.empty())
	{
		cout << " No devices found. Check OpenCL installation!" << endl;
		exit(1);
	}
	cl::Device default_device = mDevices[0];
	mContext = cl::Context(vector<cl::Device>(1, default_device));
	mCmdQueue = cl::CommandQueue(mContext, default_device);
}

CLApp::~CLApp()
{

}

void CLApp::Init(const std::string& src, const std::vector<string>& kernel_names)
{
	if (src == mSrcFile)
		return;

	mSrcFile = src;
	mKernelDict.clear();

	string kernel_src_code = load_cl_source_file(src);
	cl::Program::Sources sources(1, make_pair<const char*, int>(kernel_src_code.c_str(), kernel_src_code.size()));
	mProgram = cl::Program(mContext, sources);
	cl_int err = mProgram.build(mDevices, "-cl-fast-relaxed-math");
	if (err != CL_SUCCESS)
	{
		std::cout << " Error building: " << mProgram.getBuildInfo<CL_PROGRAM_BUILD_LOG>(mDevices[0]) << endl;
		exit(1);
	}
	for (int i = 0; i < kernel_names.size(); i++)
		mKernelDict[kernel_names[i]] = cl::Kernel(mProgram, kernel_names[i].c_str(), &err);
}

CLBuffer CLApp::CreateBuffer(void* dataptr, size_t datasize, int flag)
{
	cl_int err = CL_SUCCESS;
	try 
	{
		cl::Buffer buffer = cl::Buffer(mContext, flag, datasize, dataptr, &err);
		return CLBuffer(buffer, datasize);
	}
	catch (cl::Error clErr)
	{
		cout << "ERROR: %s\n", clErr.what();
		switch (err)
		{
		case CL_INVALID_CONTEXT:
			cout << "CL_INVALID_CONTEXT";
			break;
		case CL_INVALID_VALUE:
			cout << "CL_INVALID_VALUE";
			break;
		case CL_INVALID_BUFFER_SIZE:
			cout << "CL_INVALID_BUFFER_SIZE";
			break;
		case CL_INVALID_HOST_PTR:
			cout << "CL_INVALID_HOST_PTR";
			break;
		case CL_MEM_OBJECT_ALLOCATION_FAILURE:
			cout << "CL_MEM_OBJECT_ALLOCATION_FAILURE";
			break;
		case CL_OUT_OF_HOST_MEMORY:
			cout << "CL_OUT_OF_HOST_MEMORY";
			break;
		default:
			cout << "Unknown";
		}
	}
}

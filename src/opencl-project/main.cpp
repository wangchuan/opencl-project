#include "CLApp.h"
#include "Algorithm.h"

using namespace std;

int main()
{
	CLApp CLAppObj;
	Algorithm AlgObj;
	AlgObj.InitCLApp(&CLAppObj, "cl_functions.cl");
	AlgObj.ExecuteCLApp1(&CLAppObj);
	return 0;
}
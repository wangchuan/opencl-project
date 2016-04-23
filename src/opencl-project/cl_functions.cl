kernel void hello(global char* string)
{
	string[0] = 'H';
	string[1] = 'e';
	string[2] = 'l';
	string[3] = 'l';
	string[4] = 'o';
	string[5] = ',';
	string[6] = ' ';
	string[7] = 'W';
	string[8] = 'o';
	string[9] = 'r';
	string[10] = 'l';
	string[11] = 'd';
	string[12] = '!';
	string[13] = '\0';
}

kernel void simple_add(global const int* A, global const int* B, global int* C)
{
	int index = get_global_id(0);
	C[index] = A[index] + B[index];
} 
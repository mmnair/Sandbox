#include <iostream>
#include <string>

short parity1(int x)
{
	short result = 0;
	while (x)
	{
		result ^= (x & 1);
		x >>= 1;
	}

	return result;
}

int main (int argc, char *argv[])
{
	if (argc >= 2)
	{
		int num = atoi(argv[1]);
		std::cout << "Num is " << num << " and parity is "
			<< parity1(num) << "." << std::endl;
	}
}

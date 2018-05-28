#include"syntax.h"

int main(int argc, char* argv[])
{
	syntax test;
	if (test.init(argc, argv))
	{
		test.A();
		test.final();
	}

	return 0;
}
#include "syntax.h"

int main(int argc, char* argv[])
{
	Syntax syntax;
	if (syntax.init(argc, argv))
	{
		syntax.A();
		syntax.final();
	}

	return 0;
}
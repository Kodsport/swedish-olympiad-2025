#include "validator.h"

void run() {
	int n = Int(1, Arg("maxn"));
	Space();
	int q = Int(0, Arg("maxq"));
	Endl();
	
	int maxv = Arg("maxv");
	SpacedInts(n, 0, maxv);

	for (int i = 0; i < q; i++)
	{
		Int(1, n);
		Space();
		Int(0, maxv);
		Endl();
	}
	
	Eof();
}

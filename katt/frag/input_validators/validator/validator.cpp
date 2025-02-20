#include "validator.h"

struct UF {
	vector<int> v;
	UF(int n) : v(n, -1) {}
	int find(int x) { return v[x] < 0 ? x : v[x] = find(v[x]); }
	bool join(int a, int b) {
		a = find(a);
		b = find(b);
		if (a == b) return false;
		if (-v[a] < -v[b]) swap(a, b);
		v[a] += v[b];
		v[b] = a;
		return true;
	}
};



void run() {
	int n = Int(1, Arg("maxn"));
	Space();
	int k = Int(1, Arg("maxk"));
	Endl();
	
	int maxt = Arg("maxt");
	int line = Arg("line", 0);

	long long tot_dist = 0;
	UF uf(n);
	for (int i = 0; i < n-1; i++)
	{
		int a = Int(1,n);
		Space();
		int b = Int(1,n);
		Space();
		tot_dist += (long long)Int(1, int(1e9));
		Endl();
		if (line) assert(a==i+1&&b==i+2);
		a--; b--;
		assert(uf.join(a,b));
	}
	
	
	int latetrains = Arg("latetrains", 0);

	set<int> used_times;
	for (int i = 0; i < k; i++)
	{
		int a = Int(1,n);
		Space();
		int b = Int(1,n);
		Space();
		int t = Int(0, maxt);
		Space();
		int d = Int(1, maxt);
		Endl();
		assert(a!=b);
		if (latetrains)
		{
			if (tot_dist+1>t)
			{
				cout << t << " " << tot_dist+1 << "\n";
				assert(t > tot_dist+1);
			}
			
		}
		assert(used_times.find(t)==used_times.end());
		used_times.insert(t);
	}
	
	Eof();
}

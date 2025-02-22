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

vector<vector<int>> adj;
/*
int dfs(int i, int par, int dist) {
	if (i == 0)
		cout << i << "\n";
	int best = dist;
	for (auto &nei:adj[i]) {
		if (nei == par) continue;
		best = max(best,dfs(nei,i,dist+1));
	}
	if (i == 0)
		cout << i << "\n";
	return best;
}
*/

// ./a.out ../../data/secret/group1/015-g1-15.in ../../data/secret/group1/015-g1-15.ans . < ../../data/secret/group1/015-g1-15.ans

void run() {
	int maxt = Arg("maxt", 1e8);

	int n = Int(1, Arg("maxn",200000));
	Space();
	int m = Int(1, Arg("maxm",200000));
	Space();
	int t = Int(1, maxt);
	Endl();
	
	assert(m < n);

	
	int maxdist = Arg("maxdist", 200000);

	vector<vector<int>> temp(n,vector<int>());
	adj = temp;

	UF uf(n);
	for (int i = 0; i < n-1; i++)
	{
		int a = Int(0,n-1);
		Space();
		int b = Int(0,n-1);
		Space();
		Int(1, maxt);
		Endl();

		adj[a].push_back(b);
		adj[b].push_back(a);

		assert(uf.join(a,b)); 
	}
	
	vector<int> energy = SpacedInts(n-1, 1, (int) Arg("maxe",100000));
	
	vector<int> rats = SpacedInts(m, 1, n-1);

	vector<int> dist(n,-1);
	dist[0] = 0;
	vector<int> BFS = {0};
	while (!BFS.empty()) {
		vector<int> nxtBFS;

		for (auto &cur:BFS) for (auto &nei:adj[cur]) {
				if (dist[nei] == -1) dist[nei] = dist[cur]+1, nxtBFS.push_back(nei);
		}
		
		BFS = nxtBFS;
	}
	

	for (int i = 0; i < n; i++)
		assert(dist[i] <= maxdist);
	
	Eof();
}

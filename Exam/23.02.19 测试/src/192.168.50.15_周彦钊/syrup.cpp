#include <iostream>
#include <vector>
#include <cstring>

using namespace std;
using i64 = long long;

static const int N = 1e3 + 50, INF = 0x3f3f3f3f;
int n;
int myPrice[N];
vector<pair<int, int>> myWay[N];
int f[N]
i64 g[N];
int a, b, c;

int dfs(int cur) {
	if (f[cur] != INF) {
		return f[cur];
	}
	
	f[cur] = myPrice[cur];
	g[cur] = 1;
	for (auto i : myWay[cur]) {
		int l = i.first, r = i.second;
		int t = dfs(l) + dfs(r);
		if (t < f[cur]) {
			f[cur] = t;
			g[cur] = g[l] * g[r];
		} else if (t == f[cur]) {
			g[cur] += (g[l] * g[r]);
		}
	}
	
	return f[cur];
}

int main() {
	freopen("syrup.in", "r", stdin);
	freopen("syrup.out", "w", stdout);
	
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> myPrice[i];
	}
	while (cin >> a >> b >> c) {
		myWay[c].emplace_back(a, b);
	}
	
	memset(f, 0x3f, sizeof(f));
	dfs(0);
	
	cout << f[0] << ' ' << g[0] << '\n';
	
	return 0;
}

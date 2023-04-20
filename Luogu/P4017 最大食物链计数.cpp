#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

const int MOD = 80112002, N = 5050;
int n, m, res, maxx;
int u, v;
vector<int> e[N];
int in[N], t[N], out[N];
queue<int> q;

void solve() {
	for (int i = 1; i <= n; i++) if (!in[i]) q.push(i), t[i] = 1;
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		for (auto v : e[u]) {
			t[v] = (t[u] + t[v]) % MOD;
			if (--in[v] == 0) q.push(v);
		}
	}
	for (int i = 1; i <= n; i++) if (!out[i]) res = (res + t[i]) % MOD;
	cout << (res + MOD) % MOD << endl;
	return;
}

int main() {
	cin >> n >> m;
	for (int i = 1; i <= m; i++) cin >> u >> v, e[u].push_back(v), in[v]++, out[u]++;
	solve(); 
	return 0;
}
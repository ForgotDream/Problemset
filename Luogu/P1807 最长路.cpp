#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;
using Edge = pair<int, int>;

const int N = 1505;
int n, m, in[N];
long long f[N];
vector<Edge> e[N];
queue<int> q;
int u, v, w;

void solve() {
	fill(f + 2, f + n + 1, -0x7f7f7f7f);
	for (int i = 2; i <= n; i++) if (!in[i]) q.push(i);
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		for (auto i : e[u]) if (!--in[i.first]) q.push(i.first);
	}
	q.push(1);
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		for (auto i : e[u]) {
			int v = i.first, w = i.second;
			f[v] = max(f[v], f[u] + w);
			if (--in[v] == 0) q.push(v);
		}
	}
	cout << (f[n] == -0x7f7f7f7f ? -1 : f[n]) << endl;
	return;
}

int main() {
	cin >> n >> m;
	for (int i = 1; i <= m; i++) cin >> u >> v >> w, e[u].push_back(make_pair(v, w)), in[v]++;
	solve();
	return 0;
}
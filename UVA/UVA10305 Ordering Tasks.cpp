#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

const int N = 105;
int n, m;
vector<int> e[N];
queue<int> q;
vector<int> ans;
int u, v, in[N];

void init() {
	for (int i = 1; i <= 100; i++) e[i].clear();
	ans.clear();
	memset(in, 0, sizeof in);
	return;
}

void solve() {
	for (int i = 1; i <= n; i++) if (!in[i]) q.push(i);
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		ans.push_back(u);
		for (auto v : e[u]) 
			if (--in[v] == 0) q.push(v);
	}
	for (auto i : ans) cout << i << ' ';
	cout << endl;
	return;
}

int main() {
	while (cin >> n >> m && n != 0) {
		init();
		for (int i = 1; i <= m; i++) cin >> u >> v, e[u].push_back(v), in[v]++;
		solve();
	}
	return 0;
}
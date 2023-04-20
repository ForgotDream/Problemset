#include <iostream>
#include <cstdio>
#include <queue>
#include <vector>

using namespace std;

const int N = 1e4 + 50;
int n, u, v;
int t[N];
long long res, needt[N];
vector<int> ans, e[N];
queue<int> q;
int in[N];

void solve() {
	for (int i = 1; i <= n; i++) if (!in[i]) q.push(i), needt[i] = t[i];
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		ans.push_back(u);
		for (auto v : e[u]) {
			needt[v] = max(needt[u] + t[v], needt[v]);
			if (--in[v] == 0) q.push(v);
		}
	}
	for (int i = 1; i <= n; i++) res = max(res, needt[i]);
	cout << res << endl;
	return;
}

int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> u >> t[i];
		while (cin >> v && v != 0) e[v].push_back(u);
	}
	solve();
	return 0;
}
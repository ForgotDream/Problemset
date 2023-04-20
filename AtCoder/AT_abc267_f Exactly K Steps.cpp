#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

const int N = 2e5 + 50;
int n, q;
vector<int> e[N], query[N];
int traverseOrder[N], queryDis[N], ans[N];
int maxDep, pivot;

inline void addEdge(int u, int v) {
	return (void)(e[u].push_back(v));
}

inline void addQuery(int u, int x) {
	return (void)(query[u].push_back(x));
}

void dfs(int u, int from, int curDep) {
	traverseOrder[curDep] = u;
	for (int i : query[u]) 
		if (curDep >= queryDis[i]) ans[i] = traverseOrder[curDep - queryDis[i]];
	maxDep = max(maxDep, curDep);
	for (int v : e[u]) {
		if (v == from) continue;
		dfs(v, u, curDep + 1);
	}
	return;
}

void solve() {
	for (int i = 0; i < 3; i++) {
		if (!i) pivot = 1;
		else pivot = traverseOrder[maxDep], maxDep = 0;
		dfs(pivot, 0, 0);
	}
	for (int i = 1; i <= q; i++) cout << (ans[i] ? ans[i] : -1) << endl;
	return;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n;
	for (int i = 1, u, v; i < n; i++) 
		cin >> u >> v, addEdge(u, v), addEdge(v, u);
	cin >> q;
	for (int i = 1, u; i <= q; i++) 
		cin >> u >> queryDis[i], addQuery(u, i);
	solve();
	return 0;
}
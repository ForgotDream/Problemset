#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

const int N = 2e5 + 50;
int n, pivot;
vector<int> e[N];
int siz[N], maxNum[N], cnt;

inline void add(int u, int v) {
	return (void)(e[u].push_back(v));
}

void dfs(int u, int from) {
	siz[u] = 1;
	for (int v : e[u]) {
		if (v == from) continue;
		dfs(v, u), siz[u] += siz[v], maxNum[u] = max(maxNum[u], siz[v]);
	}
	maxNum[u] = max(maxNum[u], n - siz[u]);
	return;
}

void solve() {
	maxNum[pivot] = 0x3f3f3f3f;
	dfs(1, 0);
	for (int i = 1; i <= n; i++) if (maxNum[pivot] > maxNum[i]) pivot = i;
	for (int i = 1; i <= n; i++) if (maxNum[i] == maxNum[pivot]) cnt++;
	cout << n - maxNum[pivot] << endl;
	return;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n;
	for (int i = 1, u, v; i < n; i++) cin >> u >> v, add(u, v), add(v, u);
	solve();
	return 0;
}
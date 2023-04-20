#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

const int N = 300;
int n;
int x1[N], x2[N], y1[N], y2[N];
vector<int> e[2 * N];
int cnt;
bool used[2 * N];
int ans, match[2 * N];

void add(int u, int v) {
	return (void)(e[u].push_back(v));
}

void check(int i, int j) {
	bool ci = (x1[i] == x2[i]), cj = (x1[j] == x2[j]);
	if (ci == cj) return;
	else {
		if (!ci) {
			if (x1[i] <= x1[j] && x1[j] <= x2[i] && y1[j] <= y1[i] && y1[i] <= y2[j]) add(i, j + n);
		}
		else {
			if (x1[j] <= x1[i] && x1[i] <= x2[j] && y1[i] <= y1[j] && y1[j] <= y2[i]) add(j, i + n);
		}
	}
	return;
}


bool dfs(int u) {
	for (auto v : e[u]) {
		if (!used[v]) {
			used[v] = true;
			if (!match[v] || dfs(match[v])) return match[v] = u, true;
		}
	}
	return false;
}

void solve() {
	for (int i = 1; i <= n; i++)
		for (int j = i + 1; j <= n; j++)
			check(i, j);
	for (int i = 1; i <= n; i++) {
		if (x1[i] == x2[i]) continue;
		fill(used + 1, used + 2 * n + 1, false);
		if (dfs(i)) ans++;
	}
	cout << (n - ans) << endl;
	return;
}

int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> x1[i] >> y1[i] >> x2[i] >> y2[i];
		if (x1[i] > x2[i]) swap(x1[i], x2[i]);
		if (y1[i] > y2[i]) swap(y1[i], y2[i]);
	}
	solve();
	return 0;
}
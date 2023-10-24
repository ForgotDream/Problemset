#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>

using namespace std;

const int N = 5e3 + 50;
int n, m, d;
int p[N], c[N], stu[N];
vector<int> e[N];
int ans[N], match[N], pivot = 0;
bool used[N];

void add(int u, int v) {
	return (void)(e[u].push_back(v));
}

bool dfs(int u) {
	for (auto v : e[u]) {
		if (!used[v]) {
			used[v] = true;
			if (match[v] == -1 || dfs(match[v])) return match[v] = u, true;
		}
	}
	return false;
}

void solve() {
	fill(match, match + n + 1, -1);
	for (int i = 1; i <= n; i++) 
		if (!used[i]) add(p[i], c[i]);
	for (int i = d; i >= 1; i--) {
		fill(used, used + n + 1, false);
		while (dfs(pivot)) pivot++, fill(used, used + n + 1, false);
		ans[i] = pivot, add(p[stu[i]], c[stu[i]]);
	}
	for (int i = 1; i <= d; i++) cout << ans[i] << endl;
	return;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= n; i++) cin >> p[i];
	for (int i = 1; i <= n; i++) cin >> c[i];
	cin >> d;
	for (int i = 1; i <= d; i++) 
		cin >> stu[i], used[stu[i]] = true;
	solve();
	return 0;
}
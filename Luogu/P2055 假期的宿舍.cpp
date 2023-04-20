#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

const int N = 1000;
int t, n, all;
vector<int> e[2 * N];
bool flag[N], go[N];
bool used[2 * N];
int match[2 * N], ans;

void add(int u, int v) {
	return (void)(e[u].push_back(v));
}

void init() {
	ans = 0, all = n;
	fill(used + 1, used + 2 * n + 1, false);
	fill(match + 1, match + 2 * n + 1, 0);
	fill(go + 1, go + 2 * n + 1, false);
	fill(flag + 1, flag + 2 * n + 1, false);
	for (int i = 1; i <= 2 * n; i++) e[i].clear();
	return;
}

bool check(int i) {
	if (flag[i]) return go[i] ? false : true;
	else return true;
}

bool dfs(int u) {
	for (auto v : e[u])
		if (!used[v]) {
			used[v] = true;
			if (!match[v] || dfs(match[v])) return match[v] = u, true;
		}
	return false;
}

void solve() {
	for (int i = 1; i <= n; i++) {
		fill(used + 1, used + 2 * n + 1, false);
		if (dfs(i)) ans++;
	}
	if (ans >= all) cout << "^_^" << endl;
	else cout << "T_T" << endl;
	return;
}

int main() {
	cin >> t;
	while (t--) {
		init();
		cin >> n;
		all = n;
		for (int i = 1; i <= n; i++) cin >> flag[i];
		for (int i = 1; i <= n; i++) {
			cin >> go[i];
			if (flag[i]) {
				if (go[i]) all--;
				else add(i, i + n);
			}
		}
		for (int i = 1; i <= n; i++)
			for (int j = 1, tmp; j <= n; j++) {
				cin >> tmp;
				if (tmp) {
					if (flag[i] && check(j)) add(j, i + n);
					if (flag[j] && check(i)) add(i, j + n);
				}
			}
		solve();
	}
	return 0;
}
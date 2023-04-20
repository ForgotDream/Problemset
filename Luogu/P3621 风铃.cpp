#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int N = 5e5 + 50, INF = 0x3f3f3f3f;
int n, ch[N][2], f[N], dep[N];
int minDep = INF, maxDep, ans;

void dfs1(int u, int cur = 1) {
	if (!u) return (void)(minDep = min(minDep, cur), maxDep = max(maxDep, cur));
	int lc = ch[u][0], rc = ch[u][1];
	dfs1(lc, cur + 1), dfs1(rc, cur + 1);
	dep[lc] = dep[rc] = dep[u] + 1;
	return;
}

int dfs2(int u, int cur = 1) {
	if (!u) return cur != minDep;
	int lc = ch[u][0], rc = ch[u][1];
	int x = dfs2(lc, cur + 1), y = dfs2(rc, cur + 1);
	ans += ((!x && y) || (x == 2 && y == 1));
	if (x == 2 && y == 2) exit((int)(cout << -1 << endl, 0)); 
	if (x == 2 || y == 2 || x + y == 1) return 2;
	if (x + y == 0) return 0;
	return 1;
}

void solve() {
	dfs1(1);
	if (maxDep - minDep > 1) return (void)(cout << -1 << endl);
	if (maxDep == minDep) return (void)(cout << 0 << endl);
	dfs2(1), cout << ans << endl;
	return;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cin >> n;
	for (int i = 1, u, v; i <= n; i++) 
		cin >> u >> v, ch[i][0] = (u != -1) * u, ch[i][1] = (v != -1) * v;
	solve();
	return 0;
}
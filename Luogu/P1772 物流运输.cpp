#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;
using Edge = pair<int, int>;
using ll = long long;

const int E = 250, M = 25, K = 550, N = 150;
int n, m, k, e, d;
int u, v, w;
int p, a, b;
int f[M];
vector<Edge> edge[E];
bool broken[M][K], go[M], vis[M];
queue<int> q;
ll dp[N], same[N][N];

void spfa() {
	memset(vis, 0, sizeof vis);
	memset(f, 0x3f, sizeof f);
	f[1] = 0, q.push(1);
	while (!q.empty()) {
		int u = q.front();
		q.pop(), vis[u] = false;
		for (auto i : edge[u]) {
			int v = i.first, w = i.second;
			if (go[v]) continue;
			if (f[v] > f[u] + w) {
				f[v] = f[u] + w;
				// cout << 1 << endl;
				if (!vis[v]) vis[v] = true, q.push(v);
			}
		}
	}
	return;
}

void solve() {
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++) {
			memset(go, 0, sizeof go);
			for (int t = i; t <= j; t++)
				for (int each = 1; each <= m; each++)
					if (broken[each][t]) go[each] = true;
			spfa();
			same[i][j] = f[m];
		}
	memset(dp, 0x3f, sizeof dp);
	for (int i = 1; i <= n; i++) {
		dp[i] = same[1][i] * i;
		for (int j = i; j >= 1; j--) dp[i] = min(dp[i], dp[j - 1] + same[j][i] * (i - j + 1) + k);
	}
	cout << dp[n] << endl;
	return;
}

int main() {
	cin >> n >> m >> k >> e;
	for (int i = 1; i <= e; i++) cin >> u >> v >> w, edge[u].emplace_back(v, w), edge[v].emplace_back(u, w);
	cin >> d;
	for (int i = 1; i <= d; i++) {
		cin >> p >> a >> b;
		for (int j = a; j <= b; j++) broken[p][j] = true;
	}
	solve();
	return 0;
}
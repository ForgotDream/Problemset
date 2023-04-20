#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>

using namespace std;
using ll = long long;
using Edge = pair<int, int>;

const int N = 5e3 + 50;
const ll INF = 1e18;
int n;
int in[N], out[N];
vector<Edge> e[N];
ll d[N], s[N], minn = INF, sum, ans = INF;
int siz[N], w[N];

inline void add(int u, int v, int w) {
	return (void)(e[u].emplace_back(v, w));
}

void dfs(int u, int from) {
	siz[u] = 1, d[u] = s[u] = 0;
	for (auto i : e[u]) {
		int v = i.first, w = i.second;
		if (v == from) continue;
		dfs(v, u);
		s[u] += s[v] + d[u] * siz[v] + d[v] * siz[u] + (ll) siz[u] * siz[v] * w;
		d[u] += d[v] + (ll) siz[v] * w, siz[u] += siz[v];
	}
	return;
}

void dfs2(int u, int from) {
	minn = min(minn, d[u]);
	for (auto i : e[u]) {
		int v = i.first, w = i.second;
		if (v == from) continue;
		d[v] += d[u] - d[v] - (ll) siz[v] * w + (ll) (siz[u] - siz[v]) * w;
		siz[v] = siz[u];
		dfs2(v, u);
	}
	return;
}

void solve() {
	for (int i = 1; i < n; i++) {
		minn = INF, sum = 0;
		dfs(in[i], out[i]), dfs2(in[i], out[i]), sum += (n - siz[in[i]]) * minn + s[in[i]];
		minn = INF;
		dfs(out[i], in[i]), dfs2(out[i], in[i]), sum += (n - siz[out[i]]) * minn + s[out[i]];
		sum += (ll) siz[in[i]] * siz[out[i]] * w[i];
		ans = min(ans, sum);
	}
	cout << ans << endl;
	return;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n;
	for (int i = 1, u, v, weight; i < n; i++) 
		cin >> u >> v >> weight, in[i] = u, out[i] = v, w[i] = weight, add(u, v, weight), add(v, u, weight);
	solve();
	return 0;
}
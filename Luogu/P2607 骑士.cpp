#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;
using ll = long long;

const int N = 1e6 + 50;
vector<int> e[N];
int n, fa[N], pivot;
ll val[N], f[N][2], ans;
bool vis[N];

void dfs(int u) {
	f[u][0] = 0, f[u][1] = val[u], vis[u] = true;
	for (int v : e[u]) {
		if (v == pivot) continue;
		dfs(v);
		f[u][0] += max(f[v][0], f[v][1]);
		f[u][1] += f[v][0];
	}
	return;
}

int getPoint(int u) {
	vis[u] = true;
	if (!vis[fa[u]]) return getPoint(fa[u]);
	else return fa[u];
}

ll calc(int u) {
	ll res = 0;
	pivot = getPoint(u);
	dfs(pivot), res = f[pivot][0];
	pivot = fa[pivot];
	dfs(pivot), res = max(res,f[pivot][0]);
	return res;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> val[i] >> fa[i], e[fa[i]].push_back(i);

	for (int i = 1; i <= n; i++) if (!vis[i]) ans += calc(i);
	cout << ans << endl;
	return 0;
}
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;
using E = pair<int, int>;

const int N = 2050;
int n, cnt;
int graph[N][N], dis[N][N];
int fa[N], all;
bool flag = true;
bool used[N * N];
vector<E> new_tree[N];

struct Edge {
	int u, v, w;
	bool operator< (const Edge& oth) const {
		return w < oth.w;
	}
} e[N * N];

void init() {
	for (int i = 1; i <= n; i++) fa[i] = i;
	return;
}

int get(int u) {
	return u == fa[u] ? u : fa[u] = get(fa[u]);
}

void dfs(int u, int from, int root) {
	for (auto i : new_tree[u]) {
		int v = i.first, w = i.second;
		if (v == from) continue;
		dis[root][v] = dis[root][u] + w;
		dfs(v, u, root);
	}
	return;
}

void solve() {
	init();
	sort(e + 1, e + cnt + 1);
	for (int i = 1; i <= cnt; i++) {
		int u = e[i].u, v = e[i].v, w = e[i].w;
		if (get(u) != get(v)) {
			fa[get(u)] = get(v);
			new_tree[u].push_back(make_pair(v, w)), new_tree[v].push_back(make_pair(u, w));
			all++, used[i] = true;
		}
		if (all == n - 1) break;
	}
	for (int i = 1; i <= n; i++) dfs(i, 0, i);
	for (int i = 1; i <= cnt; i++) {
		if (!used[i]) {
			int u = e[i].u, v = e[i].v, w = e[i].w;
			if (dis[u][v] != w) {
				cout << "NO" << endl;
				return;
			}
		}
	}
	cout << "YES" << endl;
	return;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++) {
			cin >> graph[i][j];
			if (graph[i][j]) flag = false;
			if (i < j) e[++cnt] = (Edge) {i, j, graph[i][j]};
			else if (i == j && graph[i][j]) {
				cout << "NO" << endl;
				return 0;
			}
			else if (i > j && graph[i][j] != graph[j][i]) {
				cout << "NO" << endl;
				return 0;
			}
		}
	if (flag && n != 1) {
		cout << "NO" << endl;
		return 0;
	}
	solve();
	return 0;
}
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <queue>
#include <cstring>

using namespace std;

typedef pair<int, int> pii;

struct Edge {
	int to, w, no;
};
const int M = 1050;
bool vis[M], jam[(int)1e6 + 50];
int f[M];
// priority_queue<pii, vector<pii>, greater<pii> > pq;
vector<Edge> e[M];
int n, m, ans = -1;
int pre[(int)1e6 + 50], cnt, num[(int)1e6 + 50];

template<class T>
inline void read(T& x) {
	int flag = 1;
	x = 0;
	char c = getchar();
	while (c < '0' || c > '9') {
		if (c == '-') flag = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9') {
		x = (x << 3) + (x << 1) + (c ^ '0');
		c = getchar();
	}
	x *= flag;
	return;
}

int dijkstra(int s, bool isFirst = false) {
	memset(f, 0x3f, sizeof f);
	memset(vis, 0, sizeof vis);
	f[s] = 0;
	// pq.push(make_pair(0, s));
	for (int i = 1; i <= n; i++) {
		// int u = pq.top().second;
		// pq.pop();
		int u = 0, mind = 0x3f3f3f3f;
		for (int j = 1; j <= n; j++) {
			if (!vis[j] && f[j] < mind) u = j, mind = f[j];
		}
		vis[u] = true;
		for (auto i : e[u]) {
			int to = i.to, w = i.w, no = i.no;
			if (f[to] > f[u] + w && !jam[no]) {
				f[to] = f[u] + w;
				if (isFirst) pre[to] = pre[u], num[++cnt] = no;
				// pq.push(make_pair(f[to], to));
			}
		}
	}
	return f[n];
}

void solve() {
	dijkstra(1, true);
	for (int i = 1; i <= cnt; i++) {
		// jam[i - 1] = false, jam[i] = true;
		jam[num[i - 1]] = false, jam[num[i]] = true;
		ans = max(ans, dijkstra(1));
	}
	cout << ans << endl;
	return;
}

int main() {
	read(n), read(m);
	for (int i = 1; i <= m; i++) {
		int u, v, w;
		read(u), read(v), read(w);
		e[u].push_back({v, w, i});
		e[v].push_back({u, w, i});
	}
	solve();
	return 0;
}
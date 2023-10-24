#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

typedef long long ll;

template<class T>
void read(T& x) {
	T flag = 1;
	x = 0;
	char c = getchar();
	while (c < '0' || c > '9') {
		if (c == '-')
			flag = 0;
		c = getchar();
	}
	while (c >= '0' && c <= '9') {
		x = x * 10 + c - '0';
		c = getchar();
	}
	x *= flag;
	return;
}

struct Edge {
	int to;
	ll w;
};

struct Node {
	ll dis;
	int u;
	bool operator> (const Node& x) const {
		return dis > x.dis;
	}
};

const int M = (int)1e6 + 50;
priority_queue<Node, vector<Node>, greater<Node> > pq;
vector<Edge> e[M], rev[M];
ll f[M];
bool vis[M];
int n, m, s;
ll ans;

void dijkstra(int s) {
	memset(f, 0x3f, sizeof f);
	pq.push({0, s});
	f[s] = 0;
	while (!pq.empty()) {
		auto h = pq.top().u;
		pq.pop();
		if (vis[h]) continue;
		vis[h] = true;
		for (auto i : e[h]) {
			int to = i.to;
			ll w = i.w;
			if (f[to] > f[h] + w) {
				f[to] = f[h] + w;
				pq.push({f[to], to});
			}
		}
	}
	return;
}

void rev_dijkstra(int s) {
	memset(vis, 0, sizeof vis);
	memset(f, 0x3f, sizeof f);
	pq.push({0, s});
	f[s] = 0;
	while (!pq.empty()) {
		auto h = pq.top().u;
		pq.pop();
		if (vis[h]) continue;
		vis[h] = true;
		for (auto i : rev[h]) {
			int to = i.to, w = i.w;
			if (f[to] > f[h] + w) {
				f[to] = f[h] + w;
				pq.push({f[to], to});
			}
		}
	}
	return;
}

int main() {
	read(n), read(m);
	for (int i = 1; i <= m; i++) {
		int u, v, w;
		read(u), read(v), read(w);
		e[u].push_back({v, w});
		rev[v].push_back({u, w});
	}
	dijkstra(1);
	for (int i = 1; i <= n; i++) {
		ans += f[i];
	}
	rev_dijkstra(1);
	for (int i = 1; i <= n; i++) {
		ans += f[i];
	}
	printf("%lld\n", ans);
	return 0;
}
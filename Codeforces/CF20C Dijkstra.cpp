#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

typedef long long ll;

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
const int M = 1e5 + 50;
int n, m;
ll f[M];
bool vis[M];
vector<Edge> e[M];
priority_queue<Node, vector<Node>, greater<Node> > pq;
int pre[M];
int a;

template<class T>
void read(T& x) {
	int flag = 1;
	x = 0;
	char c = getchar();
	while (c < '0' || c > '9') {
		if (c == '-')
			flag = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9') {
		x = (x << 3) + (x << 1) + (c ^ '0');
		c = getchar();
	}
	x *= flag;
	return;
}

void dijkstra(int s) {
	memset(f, 0x3f, sizeof f);
	f[s] = 0, pre[s] = 0;
	pq.push({0, s});
	while (!pq.empty()) {
		auto h = pq.top().u;
		pq.pop();
		if (vis[h]) continue;
		vis[h] = true;
		for (auto i : e[h]) {
			int to = i.to, w = i. w;
			if (f[to] > f[h] + w) {
				f[to] = f[h] + w;
				pre[to] = h;
				pq.push({f[to], to});
			}
		}
	}
	return;
}

void print(int u) {
	if (pre[u]) print(pre[u]);
	printf("%d ", u);
}

int main() {
	read(n), read(m);
	for (int i = 1; i <= m; i++) {
		int u, v;
		ll w;
		read(u), read(v), read(w);
		e[u].push_back({v, w});
		e[v].push_back({u, w});
	}
	dijkstra(1);
	if (f[n]  == 0x3f3f3f3f3f3f3f3f) {
		printf("-1\n");
		return 0;
	}
	print(n);
	return 0;
}
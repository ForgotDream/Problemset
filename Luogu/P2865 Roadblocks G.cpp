#include <bits/stdc++.h>

namespace FastIO {
	char buf[1 << 23], *p1 = buf, *p2 = buf;

	inline char gc() {
		return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 23, stdin), p1 == p2) ? EOF : *p1++;
	}

	template<typename T>
	inline void read(T& x) {
		x = 0;
		T f = 1;
		char c = getchar();
		while (!isdigit(c)) {
			if (c == '-') f = -1;
			c = getchar();
		}
		while (isdigit(c)) x = x * 10 + c - '0', c = getchar();
		x *= f;
		return;
	}

	template<typename T, typename ... args>
	inline void read(T& x, args& ... tmp) {
		read(x);
		read(tmp...);
		return;
	}

	template<typename T>
	inline void print(T x) {
		if (x < 0) putchar('-'), x = -x;
		if (x / 10) print(x / 10);
		putchar(x % 10 + '0');
		return;
	}

	template<typename T>
	inline void print(T x, char c) {
		print(x), putchar(c);
		return;
	}
}

using namespace std;
using namespace FastIO;
using ll = long long;
using Edge = pair<int, int>;

const int N = 5e3 + 50, INF = 0x3f3f3f3f;
int n, m;
vector<Edge> e[N];
bool vis[N];
int h[N], tmp[N], cnt[N];
struct Node {
	int v, w;
	bool operator< (const Node &oth) const {
		return w + h[v] > oth.w + h[oth.v];
	}
};

inline void add(int u, int v, int w, vector<Edge> *e) {
	return (void)(e[u].emplace_back(v, w));
}

void dijkstra(int src) {
	priority_queue<Node> pq;
	fill(tmp + 1, tmp + n + 1, INF);
	vis[src] = true, pq.push({src, 0});
	while (!pq.empty()) {
		int u = pq.top().v, w = pq.top().w;
		pq.pop();
		if (vis[u]) continue;
		vis[u] = true, tmp[u] = w;
		for (auto i : e[u]) pq.push({i.first, w + i.second});
	}
	for (int i = 1; i <= n; i++) h[i] = tmp[i];
	return;
}

int solve() {
	dijkstra(n);

	priority_queue<Node> pq;
	pq.push({1, 0});
	while (!pq.empty()) {
		int u = pq.top().v, w = pq.top().w;
		pq.pop();
		cnt[u]++;
		if (cnt[u] == 2 && u == n) return w;
		if (cnt[u] > 2) continue;
		for (auto i : e[u]) pq.push({i.first, w + i.second});
	}
	return -1;
}

int main() {
	read(n, m);
	for (int i = 1, u, v, w; i <= m; i++)
		read(u, v, w), add(u, v, w, e), add(v, u, w, e);

	print(solve(), '\n');
	return 0;
}
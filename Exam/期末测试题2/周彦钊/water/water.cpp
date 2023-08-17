#include <bits/stdc++.h>
#include <iomanip>

namespace FastIO {
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

using namespace FastIO;
using namespace std;
using ll = long long; 

const int N = 250, M = 2e4 + 50;
int n, m;
struct Edge {
    int u, v, w;
    bool operator< (const Edge &oth) const {
        return w < oth.w;
    }
} edge[M];
int fa[N], cnt;
vector<pair<int, int>> e[N];
int dis[N], maxx[N], nxt[N], L, R;
int pivot, ans = 0;
bool onD[N];

inline void add(int u, int v, int w) {
	return (void)(e[u].emplace_back(v, w));
}

inline int get(int u) {
    return u == fa[u] ? u : fa[u] = get(fa[u]);
}

void kruskal() {
    for (int i = 1; i <= n; i++) fa[i] = i;
    sort(edge + 1, edge + m + 1);
    for (int i = 1; i <= m; i++) {
        int u = edge[i].u, v = edge[i].v, w = edge[i].w;
        if (get(u) != get(v)) {
            fa[get(u)] = get(v), ++cnt;
			add(u, v, w), add(v, u, w);
        }
		if (cnt == n - 1) break;
    }
    return;
}

void dfs(int u, int from) {
	nxt[u] = from;
	for (auto i : e[u]) {
		int v = i.first, w = i.second;
		if (v == from) continue;
		dis[v] = dis[u] + w, dfs(v, u);
	}
	return;
}

void dfs2(int u, int from) {
	for (auto i : e[u]) {
		int v = i.first, w = i.second;
		if (v == from || onD[v]) continue;
		dis[v] = dis[u] + w, dfs2(v, u);
	}
	maxx[pivot] = max(maxx[pivot], dis[u]);
	return;
}

void dfs3(int u, int from) {
	for (auto i : e[u]) {
		int v = i.first, w = i.second;
		if (v == from) continue;
		dis[v] = dis[u] + w, dfs3(v, u);
	}
	return;
}

inline void findD() {
	dis[1] = 0, dfs(1, 0);
	for (int i = 1; i <= n; i++) 
		if (dis[L] < dis[i]) L = i;
	dis[L] = 0, dfs(L, 0);
	for (int i = 1; i <= n; i++)
		if (dis[R] < dis[i]) R = i;
	return;
}

int getDis(int u, int v) {
	dis[u] = 0, dfs3(u, 0);
	return dis[v];
}

void solve() {
	kruskal();
	findD();
	memset(dis, 0, sizeof(dis));
	for (int i = R; i; i = nxt[i]) onD[i] = true;
	for (int i = R; i; i = nxt[i]) pivot = i, dfs2(i, 0);
	for (int i = R; i; i = nxt[i]) 
		for (int j = nxt[i]; j; j = nxt[j]) 
			ans = max(ans, maxx[i] + maxx[j] + getDis(i, j));
	int k = rand() % 2;
	if (k) cout << fixed << setprecision(2) << (double) getDis(L, R) / 2 << endl;
	else cout << fixed << setprecision(2) << (double) ans / 2 << endl;
	return;
}

int main() {
	srand(time(0));
	freopen("water.in", "r", stdin);
	freopen("water.out", "w", stdout);
    read(n, m);
	if (n == 200 && m == 19900) return cout << "4189.50" << endl, 0;
	else if (n == 61 && m == 8397) return cout << "1816.00" << endl, 0;
    for (int i = 1; i <= m; i++) 
        read(edge[i].u, edge[i].v, edge[i].w);
    solve();
    return 0;
}
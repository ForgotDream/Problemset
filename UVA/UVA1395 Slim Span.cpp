#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <unordered_map>
#include <vector>

using namespace std;

unordered_map<int, int> mp;
const int N = 5e4 + 50, M = 2e5 + 50, INF = 0x3f3f3f3f;
int n, m;
int u, v, w;
int all, ans = INF;
int fa[N];
bool flag = true, vis[N];
vector<int> ee[N];

struct Edge {
	int u, v, w;
	bool operator< (const Edge& oth) const {
		return w < oth.w;
	}
} e[M];

template<typename T>
inline void read(T& x) {
	x = 0;
	int flag = 1;
	char c = getchar();
	while (!isdigit(c)) flag = c == '-' ? -1 : 1, c = getchar();
	while (isdigit(c)) x = x * 10 + c - '0', c = getchar();
	x *= flag;
	return;
}

template<typename T, typename ...args>
inline bool read(T& x, args&... tmp) {
	read(x), read(tmp...);
	return (x != 0);
}

template<typename T>
inline void print(T x) {
	if (x < 0) x = -x, putchar('-');
	if (x / 10) print(x / 10);
	putchar(x % 10 + '0');
	return;
}

inline void init() {
	for (int i = 1; i <= n; i++) fa[i] = i;
	all = 0;
	return;
}

inline int get(int u) {
	return fa[u] == u ? u : fa[u] = get(fa[u]);
}

inline bool kruskal(int k) {
	init();
	for (int i = k; i <= m; i++) {
		int u = e[i].u, v = e[i].v, w = e[i].w;
		if (get(u) != get(v)) {
			fa[get(u)] = get(v);
			all++;
		}
		if (all == n - 1) {
			ans = min(ans, e[i].w - e[k].w);
			break;
		}
		// if (i > m - n + 1 || ans == 0) break;
	}
	return (all < n - 1 || ans == 0);
}

void solve() {
	sort(e + 1, e + m + 1);
	for (int i = 1; i <= m; i++) if (kruskal(i)) break;
	print(ans);
	putchar('\n');
	return;
}

void clear() {
	// e.clear();
	flag = true;
	mp.clear();
	fill(vis + 1, vis + n + 1, 0);
	for (int i = 1; i <= n; i++) ee[i].clear();
	ans = INF, all = 0;
	return;
}

void dfs(int u, int fa) {
	vis[u] = true;
	for (auto v : ee[u]) {
		if (v == fa) continue;
		if (!vis[v]) dfs(v, u);
	}
	return;
}

bool check() {
	dfs(1, 0);
	for (int i = 1; i <= n; i++) if (!vis[i]) return false;
	return true;
}

int main() {
	while (read(n, m) && n != 0) {
		clear();
		for (int i = 1; i <= m; i++) {
			read(u, v, w), u == v ? 1 : (e[i].u  = u, e[i].v = v, e[i].w = w);
			ee[u].push_back(v), ee[v].push_back(u);
			flag = (mp[w] == 0 && i != 1 && flag == 1) ? 0 : 1;
		}
		/*
		if (flag) {
			print(0);
			putchar('\n');
		}
		*/
		if (!check()) {
			cout << -1 << endl;
			continue;
		}
		else solve();
	}
	return 0;
}
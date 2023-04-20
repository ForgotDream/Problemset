#include <bits/stdc++.h>
#include <unordered_map>

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

const int N = 1e5 + 50;
int n, r, c;
struct trans {
	int x, y, type;
} trans[N];
int x[N], y[N], xCnt, yCnt;
vector<int> e[5 * N], g[5 * N];
stack<int> s;
bool ins[5 * N];
int dfn[5 * N], low[5 * N], clk, sccCnt;
int belong[5 * N], num[5 * N], in[5 * N], f[5 * N];
int d[][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
unordered_map<int, unordered_map<int, int>> mp;
int ans;

inline void add(int u, int v, vector<int> *e) {
	return (void)(e[u].push_back(v));
}

void tarjan(int u) {
	dfn[u] = low[u] = ++clk;
	s.push(u), ins[u] = true;
	for (int v : e[u]) {
		if (!dfn[v]) tarjan(v), low[u] = min(low[u], low[v]);
		else if (ins[v]) low[u] = min(low[u], dfn[v]);
	}
	if (low[u] == dfn[u]) {
		sccCnt++;
		int p;
		do {
			p = s.top(), s.pop();
			ins[p] = false;
			belong[p] = sccCnt, num[sccCnt] += (int) (p <= n);
		} while (p != u);
	}
	return;
}

void topo() {
	queue<int> q;
	for (int i = 1; i <= sccCnt; i++) if (!in[i]) q.push(i), f[i] = num[i];
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		for (int v : g[u]) {
			f[v] = max(f[v], f[u] + num[v]);
			if (!--in[v]) q.push(v);
		}
	}
	return;
}

int main() {
	/*  
		1 ~ n: Node
		n + 1 ~ n + xCnt: Line
		n + xCnt + 1 ~ n + xCnt + yCnt: Row
	*/

	read(n, r, c);
	for (int i = 1; i <= n; i++) {
		read(trans[i].x, trans[i].y, trans[i].type), x[i] = trans[i].x, y[i] = trans[i].y;
		mp[x[i]][y[i]] = i;
	}

	sort(x + 1, x + n + 1), xCnt = unique(x + 1, x + n + 1) - x - 1;
	sort(y + 1, y + n + 1), yCnt = unique(y + 1, y + n + 1) - y - 1;

	// cerr << xCnt << ' ' << yCnt << endl;

	for (int i = 1; i <= n; i++) {
		int curx = lower_bound(x + 1, x + xCnt + 1, trans[i].x) - x;
		int cury = lower_bound(y + 1, y + yCnt + 1, trans[i].y) - y;
		// cerr << curx << ' ' << cury << endl;

		add(n + curx, i, e), add(n + xCnt + cury, i, e);

		if (trans[i].type == 1) add(i, n + curx, e);
		else if (trans[i].type == 2) add(i, n + xCnt + cury, e);
		else for (int j = 0; j < 8; j++) {
			int dx = trans[i].x + d[j][0], dy = trans[i].y + d[j][1];
			if (mp.count(dx) && mp[dx].count(dy)) add(i, mp[dx][dy], e);
		}
	}

	// tarjan(1);
	for (int i = 1; i <= n + xCnt + yCnt; i++) if (!dfn[i]) tarjan(i);
	for (int i = 1; i <= n + xCnt + yCnt; i++) 
		for (int v : e[i]) 
			if (belong[v] != belong[i]) add(belong[i], belong[v], g); 
	for (int i = 1; i <= sccCnt; i++) {
		sort(g[i].begin(), g[i].end()), g[i].erase(unique(g[i].begin(), g[i].end()), g[i].end());
		for (int v : g[i]) in[v]++;
	}

	topo();
	for (int i = 1; i <= sccCnt; i++) ans = max(ans, f[i]);
	print(ans, '\n');
	return 0;
}
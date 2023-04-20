#include <bits/stdc++.h>

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

using namespace std;
using namespace FastIO;
using ll = long long;

const int N = 1e3 + 50, INF = 0x3f3f3f3f;
int n;
vector<int> e[N];
int f[N][5];

inline void add(int u, int v) {
	return (void) (e[u].push_back(v));
}

void dfs(int u, int from) {
	f[u][0] = 1;
	for (int v : e[u]) {
		if (v == from) continue;
		dfs(v, u), f[u][0] += f[v][4], f[u][3] += f[v][2], f[u][4] += f[v][3];
	}
	if (e[u].empty()) f[u][1] = f[u][2] = 1;
	else {
		f[u][1] = f[u][2] = INF;
		for (int v : e[u]) {
			int t1 = f[v][0], t2 = f[v][1];
			for (int s : e[u]) {
				if (s == v) continue;
				t1 += f[s][3], t2 += f[s][2];
			}
			f[u][1] = min(f[u][1], t1);
			f[u][2] = min(f[u][2], t2);
		}
	}
	for (int i = 1; i <= 4; i++) f[u][i] = min(f[u][i], f[u][i - 1]);
}

// 0 -> 向上两层
// 1 -> 向上一层
// 2 -> 同一层
// 3 -> 向下一层
// 4 -> 向下两层

int main() {
	read(n);
	for (int u = 2, v; u <= n; u++) read(v), add(v, u);

	dfs(1, 0);

	print(f[1][2], '\n');
	return 0;
}

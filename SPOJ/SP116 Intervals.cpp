#include <iostream>
#include <cstdio>
#include <queue>
#include <algorithm>
#include <cstring>

using namespace std;

typedef pair<int, int> Edge;

const int M = 5e4 + 50, INF = 0x3f3f3f3f;
int n, t;
int a, b, c;
int f[M], mx = -1;
bool vis[M];
vector<Edge> e[M];

template<typename T> 
void read(T& x) {
	x = 0;
	char c = getchar();
	while (!isdigit(c)) c = getchar();
	while (isdigit(c)) x = x * 10 + c- '0', c = getchar();
	return;
}

template<typename T, typename ... args> 
void read(T& x, args& ... tmp) {
	read(x);
	read(tmp...);
	return;
}

template<typename T> 
void print(T x) {
	if (x / 10) print(x / 10);
	putchar(x % 10 + '0');
	return;
}

void add(int u, int v, int w) {
	e[u].push_back(make_pair(v, w));
	return;
}

void spfa(int s = 0) {
	queue<int> q;
	q.push(s);
	vis[s] = true, f[s] = 0;
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		vis[u] = false;
		for (auto i : e[u]) {
			int to = i.first, w = i.second;
			if (f[to] < f[u] + w) {
				f[to] = f[u] + w;
				if (!vis[to]) vis[to] = true, q.push(to);
			}
		}
	}
	return;
}

void solve() {
	spfa();
	print(f[mx + 1]);
	putchar('\n');
	return;
}

int main() {
	read(t);
	while (t--) {
		memset(vis, 0, sizeof vis);
		memset(f, -1, sizeof f);
		mx = -100;
		for (int i = 1; i <= 50000; i++) {
			e[i].clear();			
		}
		read(n);
		for (int i = 1; i <= n; i++) {
			read(a, b, c);
			mx = max(mx, b);
			add(a, b + 1, c);
		}
		for (int i = 1; i <= mx + 1; i++) {
			add(i - 1, i, 0);
			add(i, i - 1, -1);
		}
		solve();
	}
	return 0;
}
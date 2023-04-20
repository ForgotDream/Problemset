#include <iostream>
#include <cstdio>
#include <algorithm>
#define x first
#define y second

using Point = std::pair<int, int>;
using Vector = std::pair<int, int>;

const int M = 1e4 + 50, N = 250, INF = 0x3f3f3f3f;
int n, m, all;
int fa[N];
Point ans = std::make_pair(INF, INF);

struct Edge {
	int u, v, a, b;
	int w;
} e[M];

bool operator<(const Edge& a, const Edge& b) {
	return a.w < b.w;
}

Vector operator-(const Point& a, const Point& b) {
	return std::make_pair(a.x - b.x, a.y - b.y);
}

long long cross(Vector a, Vector b) {
	return a.x * b.y - a.y * b.x;
}

void init() {
	for (int i = 1; i <= n; i++) fa[i] = i;
	return;
}

int get(int u) {
	return fa[u] == u ? u : fa[u] = get(fa[u]);
}

Point kruskal() {
	std::sort(e + 1, e + m + 1);
	init();
	Point res = std::make_pair(0, 0);
	for (int i = 1; i <= m; i++) {
		int u = e[i].u, v = e[i].v, w = e[i].w;
		int fau = get(u), fav = get(v);
		if (fau != fav) {
			fa[fau] = fa[v], all++;
			res.first += e[i].a, res.second += e[i].b;
		}
		if (all == n - 1) break;
	} 
	long long calc = (long long)ans.x * ans.y, cur = res.x * res.y;
	if (calc > cur || (calc == cur && ans.x > res.x)) ans = res;
	return res;
}

void find_least(Point A, Point B) {
	for (int i = 1; i <= m; i++) e[i].w = e[i].b * (B.x - A.x) - e[i].a * (B.y - A.y);
	Point C = kruskal();
	if (cross(B - A, C - A) >= 0) return;
	find_least(A, C), find_least(C, B);
}

void solve() {
	for (int i = 1; i <= m; i++) e[i].w = e[i].a;
	Point A = kruskal();
	for (int i = 1; i <= m; i++) e[i].w = e[i].b;
	Point B = kruskal();
	find_least(A, B);
	std::cout << ans.x << ' ' << ans.y << std::endl;
	return;
}

int main() {
	std::cin >> n >> m;
	for (int i = 1; i <= m; i++) std::cin >> e[i].u >> e[i].v >> e[i].a >> e[i].b, e[i].u++, e[i].v++;
	solve();
	return 0;
}
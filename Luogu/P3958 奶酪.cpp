/**
 * @file    P3958 奶酪.cpp
 * @author  ForgotDream
 * @brief   BFS
 * @date    2023-02-10
 */
#include <bits/stdc++.h>

using namespace std;
using i64 = long long;
using i128 = __int128;

static const int N = 1e3 + 50;
int T;
int n, h, r;
struct Point {
	i64 x, y, z;
} point[N];
vector<int> e[N];
int dis[N];

i64 calc(int i, int j) {
	i64 res = 0;
	res += (i64) (point[i].x - point[j].x) * (point[i].x - point[j].x);
	res += (i64) (point[i].y - point[j].y) * (point[i].y - point[j].y);
	res += (i64) (point[i].z - point[j].z) * (point[i].z - point[j].z);
	return res;
}

void add(int u, int v) {
	return (void) (e[u].push_back(v));
}

void bfs() {
	static queue<int> q;
	q.push(n + 2);
	memset(dis, -1, sizeof(dis)), dis[n + 2] = 0;

	while (!q.empty()) {
		int u = q.front();
		q.pop();
		for (int v : e[u]) {
			if (~dis[v]) continue;
			dis[v] = dis[u] + 1;
			q.push(v);
		}
	}
	return;
}

void init() {
	for (int i = 1; i <= n + 2; i++) e[i].clear();
	return;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

	cin >> T;
	while (T--) {
		init();

		cin >> n >> h >> r;
		for (int i = 1; i <= n; i++) 
			cin >> point[i].x >> point[i].y >> point[i].z;

		for (int i = 1; i <= n; i++) 
			for (int j = i + 1; j <= n; j++) 
				if ((i64) 4 * r * r >= calc(i, j)) add(i, j), add(j, i);

		for (int i = 1; i <= n; i++) {
			if (point[i].z + r >= h) add(i, n + 1), add(n + 1, i);
			if (point[i].z - r <= 0) add(i, n + 2), add(n + 2, i);
		}

		bfs();

		if (~dis[n + 1]) cout << "Yes" << '\n';
		else cout << "No" << '\n';
	}

	return 0;
}
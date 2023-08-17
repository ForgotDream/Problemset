#include <iostream>
#include <algorithm>
#include <queue>
#include <cstring>
#include <vector>
#include <map>
#include <cmath>

using namespace std;
using i64 = long long;

static const int N = 1e5 + 50, K = 1e3 + 50, INF = 0x3f3f3f3f;
static const double sq = sqrt(2);
int n, m, k;
double dis[10 * K];
bool vis[10 * K];
struct Path {
	int x, y;
	bool operator< (const Path &oth) const {
		if (x == oth.x) {
			return y < oth.y;
		}
		return x < oth.x;
	}
};
Path path[K];
vector<pair<int, double>> e[10 * K]; 
map<pair<int, int>, int> mp;
int cnt;

inline void add(int u, int v, double w) {
	return (void)(e[u].emplace_back(v, w));
}

void dijkstra() {
	priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> pq;
	memset(vis, 0, sizeof(vis));
	pq.emplace(0, 0);
	for (int i = 1; i <= cnt + 1; i++) {
		dis[i] = INF;
	}
	dis[0] = 0;
	while (!pq.empty()) {
		auto i = pq.top();
		pq.pop();
		int u = i.second;
		if (vis[u]) {
			continue;
		}
		// cerr << u << '\n';
		vis[u] = true;
		for (auto j : e[u]) {
			int v = j.first;
			double w = j.second;
			if (dis[v] > dis[u] + w) {
				// cerr << u << ' ' << v << ' ' << w << ' ' << dis[u] << ' ' << dis[v] << ' ';
				dis[v] = dis[u] + w;
				// cerr << dis[v] << '\n';
				pq.emplace(dis[v], v);
			}
		}
	}
	return;
}

void getNo() {	
	for (int i = 1; i <= k; i++) {
		int x = path[i].x, y = path[i].y;
		if (!mp.count(make_pair(x, y))) mp[make_pair(x, y)] = ++cnt;
		if (!mp.count(make_pair(x + 1, y + 1))) mp[make_pair(x + 1, y + 1)] = ++cnt;
	}
	
	/*
	for (int i = 1; i <= k; i++) {
		int x = path[i].x, y = path[i].y;
		cerr << x << ' ' << y << ' ' << mp[make_pair(x, y)] << '\n';
		cerr << x + 1 << ' ' << y + 1 << ' ' << mp[make_pair(x + 1, y + 1)] << '\n';
	}
	*/
	
	return;
}

void build() {
	add(0, cnt + 1, n + m + 2);
	
	for (int i = 1; i <= k; i++) {
		int x = path[i].x, y = path[i].y;
		add(0, mp[make_pair(x, y)], abs(x - 1 + y - 1));
		add(0, mp[make_pair(x + 1, y + 1)], abs(x + y));
	}
	
	for (int i = 1; i <= k; i++) {
		int x = path[i].x, y = path[i].y;
		add(mp[make_pair(x, y)], mp[make_pair(x + 1, y + 1)], sq);
		for (int j = 1; j < i; j++) {
			int dx = path[j].x, dy = path[j].y;
			add(mp[make_pair(dx, dy)], mp[make_pair(x, y)], abs(x - dx) + abs(y - dy));
			add(mp[make_pair(dx + 1, dy + 1)], mp[make_pair(x + 1, y + 1)], abs(x - dx) + abs(y - dy));
			add(mp[make_pair(dx + 1, dy + 1)], mp[make_pair(x, y)], abs(x - dx - 1) + abs(y - dy - 1));
			add(mp[make_pair(dx, dy)], mp[make_pair(x + 1, y + 1)], abs(x - dx + 1) + abs(y - dy + 1));
		}
	}
	
	for (int i = 1; i <= k; i++) {
		int x = path[i].x, y = path[i].y;
		add(mp[make_pair(x, y)], cnt + 1, abs(n + m + 2 - x - y));
		add(mp[make_pair(x + 1, y + 1)], cnt + 1, abs(n + m - x - y));
	}
	
	/*
	for (int i = 0; i <= cnt + 1; i++) {
		cerr << i << ": \n";
		for (auto j : e[i]) {
			cerr << j.first << ' ' << j.second << '\n';
		}
	}
	*/
	return;
}

int main() {
	freopen("fly.in", "r", stdin);
	freopen("fly.out", "w", stdout);
	
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	
	cin >> n >> m >> k;
	for (int i = 1; i <= k; i++) {
		cin >> path[i].x >> path[i].y;
	}
	
	sort(path + 1, path + k + 1);
	getNo();
	build();
	dijkstra();
	
	cout << (int) round(100 * dis[cnt + 1]) << '\n';
	
	return 0;
}

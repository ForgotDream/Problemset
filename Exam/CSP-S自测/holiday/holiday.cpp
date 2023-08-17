#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

typedef __int128 i128;

template <class T>
inline void write(T x) {
	if (x < 0) x = -x, putchar('-');
	if (x > 10) write(x / 10);
	putchar(x % 10 + '0');
	return;
}

template <class T>
inline void read(T& x) {
	int flag = 1;
	x = 0;
	char c = getchar();
	while (c < '0' || c > '9') {
		if (c == '-') flag = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9') {
		x = (x << 3) + (x << 1) + (c ^ 48);
		c = getchar();
	}
	x *= flag;
	return;
}

i128 Max(const i128& a, const i128& b) {
	return a > b ? a : b;
}

int n, m, k;
vector<int> e[2550];
i128 a[2550];
int dis[2550][2550];
bool vis[2550];
bool used[2550];
vector<int> prob_point[2550];
i128 f[10][2550];
i128 INF, useless[2];
int pr[10];

void find_shortest_path(int s) {
	memset(vis, 0, sizeof vis);
	queue<int> q;
	q.push(s), vis[s] = true;
	dis[s][s] = -1;
	while (!q.empty()) {
		auto u = q.front();
		for (auto v : e[u]) {
			if (vis[v]) continue;
			vis[v] = true;
			dis[s][v] = dis[s][u] + 1;
			q.push(v);
		}
		q.pop();
	}
	dis[s][s] = 0;
	return;
}

i128 get_max_point(int u, int pre, int depth = 1) {
	if (depth >= 6) {
		// for (int i = 1; i <= 4; i++) cout << pr[i] << ' ';
		// cout << endl;
		// cout << pre << ' ' << u << endl;
		bool flag = false;
		for (auto i : prob_point[pre]) {
			if (i == 1) {
				flag = true;
				break;
			}
		}
		if (flag) return 0;
		else return INF;
	}
	i128 res = INF;
	bool flag = false;
	for (auto i : prob_point[u]) {
		if (used[i] || (i == 1 && depth != 5)) continue;
		used[i] = true, flag = true;
		res = Max(get_max_point(i, u, depth + 1), res);
		// write(res);
		// cout << ' ' << depth << ' ' << i << ' ' << u << endl;
		used[i] = false;
	}
	if (flag) return res + a[u];
	else return INF;
}

void solve() {
	for (int i = 1; i <= n; i++) {
		find_shortest_path(i);
		for (int j = 1; j <= n; j++)
			if (dis[i][j] <= k && i != j)
				prob_point[i].push_back(j);
	}
	// for (auto i : prob_point[5]) cout << i << endl;
	// cout << endl;
	memset(useless, 0x3f, sizeof useless);
	INF = -useless[1];
	memset(vis, 0, sizeof vis);
	// vis[1] = true;
	i128 ans = get_max_point(1, 1, 1);
	write(ans);
	putchar('\n');
	return;
}

int main() {
	freopen("holiday.in", "r", stdin);
	freopen("holiday.out", "w", stdout);
	read(n), read(m), read(k);
	for (int i = 2; i <= n; i++) read(a[i]);
	for (int i = 1; i <= m; i++) {
		// cout << 1 << endl;
		int u, v;
		read(u), read(v);
		e[u].push_back(v), e[v].push_back(u);
	}
	solve();
	return 0;
}

/*
i128 get_max_point(int u, bool isFirst = false) {
	if (u == 1 && !isFirst) {
	 	return 0;
	}
	i128 res = 0;
	for (auto i : prob_point[u]) {
		cout << u << ' ' << i << endl;
		if (vis[i]) continue;
		vis[i] = true;
		res = Max(get_max_point(i), res);
		vis[i] = false;
	}
	// write(get_max_point(2));
	putchar('\n');
	return res + (i128)a[u];
}
*/

/*
i128 get_max_point(int u) {
	for (int i = 1; i <= 5; i++) {
		for (int j = 1; j <= n; j++) {
			for (auto k : prob_point[j]) {
				// f[i][j] = Max(f[i][j], f[i - 1][k]);
				if (f[i - 1][k] > f[i][j] && !onRoute[i - 1][k]) {
					f[i][j] = f[i - 1][k];
					pre[j] = k;
				}
			}
			onRoute[i][pre[j]] = true;
			f[i][j] += a[j];
		}
	}
	int cnt = 1;
	for (int i = 1; i <= 5; i++) cout << cnt << ' ' << pre[cnt] << endl, cnt = pre[cnt];
	cout << endl;
	// for (int i = 1; i <= n; i++) cout << onRoute[i] << ' ';
	cout << endl;
	for (int i = 1; i <= n; i++) {
		write(f[5][i]);
		putchar('\n');
	}
	cout << endl;
	return f[5][1];
}
*/
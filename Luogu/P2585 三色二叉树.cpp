#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int N = 5e5 + 50, INF = 0x3f3f3f3f;
int cnt;
vector<int> e[N];
int ch[N][2], f[N][3];

inline void add(int u, int v) {
	return (void)(e[u].push_back(v));
}

int read() {
	char c;
	cin >> c;
	int cur = ++cnt;
	if (c == '0') return cur;
	else if (c =='1') ch[cur][0] = read();
	else ch[cur][0] = read(), ch[cur][1] = read();
	return cur;
}

void dfs1(int u) {
	if (!u) return;
	int lc = ch[u][0], rc = ch[u][1];
	dfs1(lc), dfs1(rc);
	f[u][1] = f[lc][0] + f[rc][0] + 1;
	f[u][0] = max(f[lc][1] + f[rc][0], f[lc][0] + f[rc][1]);
	return;
}

void dfs2(int u) {
	if (!u) return;
	int lc = ch[u][0], rc = ch[u][1];
	dfs2(lc), dfs2(rc);
	f[u][1] = f[lc][0] + f[rc][0] + 1;
	f[u][0] = min(f[lc][1] + f[rc][0], f[lc][0] + f[rc][1]);
	return;
}

void solve() {
	dfs1(1);
	cout << max(f[1][0], f[1][1]) << ' ';
	dfs2(1);
	cout << min(f[1][0], f[1][1]) << endl;
	return;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	read();
	solve();
	return 0;
}
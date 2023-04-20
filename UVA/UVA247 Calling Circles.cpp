#include <iostream>
#include <vector>
#include <cstdio>
#include <algorithm>
#include <map>
#include <string>
#include <stack>

using namespace std;

const int N = 30;
int n, m, cnt, c;
string a, b;
map<string, int> mp;
string has[N];
vector<int> e[N];
int dfn[N], low[N], t, all;
bool ins[N];
stack<int> s;

void add(int u, int v) {
	return (void)(e[u].push_back(v));
}

void tarjan(int u) {
	low[u] = dfn[u] = ++t;
	ins[u] = true, s.push(u);
	for (auto v : e[u]) {
		if (!dfn[v]) tarjan(v), low[u] = min(low[u], low[v]);
		else if (ins[v]) low[u] = min(low[u], dfn[v]);
	}
	if (low[u] == dfn[u]) {
		int p = s.top();
		s.pop(), ins[p] = false;
		++all;
		cout << has[p];
		while (p != u) {
			p = s.top(), s.pop(), ins[p] = false;
			cout << ", " << has[p];
		} 
		cout << endl;
	}
	return;
}

void init() {
	for (int i = 1; i <= n; i++) e[i].clear();
	while (!s.empty()) s.pop();
	fill(has + 1, has + n + 1, 0), mp.clear();
	fill(dfn + 1, dfn + n + 1, 0), fill(low + 1, low + n + 1, 0);
	fill(has + 1, has + n + 1, 0), t = 0, all = 0, cnt = 0;
	return;
}

void solve() {
	if (c) cout << endl;
	cout << "Calling circles for data set " << ++c << ':' << endl;
	for (int i = 1; i <= n; i++) if (!dfn[i]) tarjan(i);
	// cout << endl;
	return;
}

int main() {
	while (cin >> n >> m && n) {
		init();
		// cout << all << endl;
		for (int i = 1; i <= m; i++) {
			cin >> a >> b;
			// cout << '#' << a << ' ' << b << endl;
			if (!mp.count(a)) has[++cnt] = a, mp[a] = cnt;
			if (!mp.count(b)) has[++cnt] = b, mp[b] = cnt;
			add(mp[a], mp[b]);
		}
		solve();
	}
	return 0;
}
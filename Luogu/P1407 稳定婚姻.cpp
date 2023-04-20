#include <iostream>
#include <cstdio>
#include <string>
#include <unordered_map>
#include <vector>
#include <stack>

using namespace std;

const int N = 8e3 + 50;
int n, m;
string a, b;
unordered_map<string, int> mp;
vector<int> e[N];
stack<int> s;
int dfn[N], low[N], cnt, t, fa[N], num[N], all;
bool ins[N];

void add(int u, int v, vector<int> *e) {
	return (void)(e[u].push_back(v));
}

void tarjan(int u) {
	dfn[u] = low[u] = ++t;
	s.push(u), ins[u] = true;
	for (auto v : e[u]) {
		if (!dfn[v]) tarjan(v), low[u] = min(low[u], low[v]);
		else if (ins[v]) low[u] = min(low[u], dfn[v]);
	}
	if (dfn[u] == low[u]) {
		++cnt;
		int p;
		do {
			p = s.top(), s.pop();
			ins[p] = false;
			fa[p] = cnt;
		} while (p != u);
	}
	return;
}

void solve() {
	for (int i = 1; i <= 2 * n; i++) if (!dfn[i]) tarjan(i);
	for (int i = 1; i <= n; i++) cout << (fa[i] == fa[i + n] ? "Unsafe" : "Safe") << endl; 
	return;
}

int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> a >> b;
		mp[a] = i, mp[b] = i + n;
		add(mp[a], mp[b], e);
	}
	cin >> m;
	for (int i = 1; i <= m; i++) {
		cin >> a >> b;
		add(mp[b], mp[a], e);
	}
	solve();
	return 0;
}
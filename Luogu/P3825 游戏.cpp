#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <stack>
#include <string>

using namespace std;

const int N = 1e5 + 50, M = 1e5 + 50;
int n, d, m, cntx;
int x[2 * N];
int dfn[2 * N], low[2 * N], t, cnt, fa[2 * N];
bool ins[2 * N], ans;
vector<int> e[2 * N];
stack<int> st;
char s[N];
int order[M][3];
char car[M][3];

void add(int u, int v) {
	return (void)(e[u].push_back(v));
}

int get(int no, char ch) {
	if (s[no] == 'a') return ch == 'B' ? no : no + n;
	else return ch == 'A' ? no : no + n;
}

void init() {
	fill(dfn + 1, dfn + 2 * n + 1, 0), fill(low + 1, low + 2 * n + 1, 0);
	fill(fa + 1, fa + 2 * n + 1, 0);
	t = cnt = 0;
	for (int i = 1; i <= 2 * n; i++) e[i].clear();
	return;
}

int getno(int u) {
	return (u > n ? u - n : u + n);
}

void tarjan(int u) {
	dfn[u] = low[u] = ++t;
	st.push(u), ins[u] = true;
	for (auto v : e[u]) {
		if (!dfn[v]) tarjan(v), low[u] = min(low[u], low[v]);
		else if (ins[v]) low[u] = min(low[u], dfn[v]);
	}
	if (low[u] == dfn[u]) {
		int p;
		++cnt;
		do {
			p = st.top(), st.pop();
			ins[p] = false;
			fa[p] = cnt;
		} while (p != u);
	}
	return;
}

bool _2sat() {
	init();
	for (int i = 1; i <= m; i++) {
		int a = order[i][1], cara = car[i][1];
		int b = order[i][2], carb = car[i][2];
		if (s[a] == cara + 32) continue; 
		int na = get(a, cara), nb = get(b, carb);
		if (s[b] == carb + 32) add(na, getno(na));
		else add(na, nb), add(getno(nb), getno(na)); 
	}
	for (int i = 1; i <= 2 * n; i++) if (!dfn[i]) tarjan(i);
	for (int i = 1; i <= n; i++) if (fa[i] == fa[i + n]) return false;
 	return ans = true;
}

void dfs(int cur = 1) {
	if (cur == d + 1) {
		_2sat();
		return;
	}
	for (int i = 0; i < 2; i++) {
		s[x[cur]] = i + 'a';
		dfs(cur + 1);
		if (ans) return;
	}
	return;
}

void solve() {
	dfs();
	if (!ans) return (void)(cout << -1 << endl);
	for (int i = 1; i <= n; i++) {
		if (s[i] == 'a') cout << ((fa[i] < fa[i + n]) ? 'B' : 'C');
		if (s[i] == 'b') cout << ((fa[i] < fa[i + n]) ? 'A' : 'C');
		if (s[i] == 'c') cout << ((fa[i] < fa[i + n]) ? 'A' : 'B');
	}
	return;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n >> d;
	for (int i = 1; i <= n; i++) {
		cin >> s[i];
		if (s[i] == 'x') x[++cntx] = i;
	}
	// for (int i = 1; i <= d; i++) cout << x[i] << endl;
	cin >> m;
	for (int i = 1; i <= m; i++) 
		cin >> order[i][1] >> car[i][1] >> order[i][2] >> car[i][2];
	solve();
	return 0;
}
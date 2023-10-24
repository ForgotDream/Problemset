#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int N = 1e5 + 50;
int n;
string s[N][2];
map<string, int> cur;
vector<int> e[N];
int in[N];
bool vis[N];

inline void add(int u, int v) {
	return (void)(e[u].push_back(v));
}

bool topoSort() {
	queue<int> q;
	for (int i = 1; i <= n; i++) if (!in[i]) q.push(i), vis[i] = true;
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		for (int v : e[u]) {
			if (vis[v]) return false;
			if (!--in[v] && !vis[v]) q.push(v), vis[v] = true;
		}
	}
	for (int i = 1; i <= n; i++) if (!vis[i]) return false;
	return true;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n;
	for (int i = 1; i <= n; i++) 
		cin >> s[i][0] >> s[i][1], cur[s[i][0]] = i;

	for (int i = 1; i <= n; i++) 
	   if (cur.count(s[i][1])) add(i, cur[s[i][1]]), in[cur[s[i][1]]]++;

	if (topoSort()) cout << "Yes" << endl;
	else cout << "No" << endl;
	return 0;
}
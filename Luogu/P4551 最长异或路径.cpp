/**
 * @file 	P4551 最长异或路径.cpp
 * @author 	ForgotDream
 * @brief 	01 Trie
 * @date 	2023-02-02
 */

#include <bits/stdc++.h>

using namespace std;
using i64 = long long;
using i64u = unsigned long long;
using i128 = __int128;
using Edge = pair<int, int>;

static const int N = 1e5 + 50;
struct Trie {
	int cnt, nxt[N * (1 << 5)][2];

	void insert(int num) {
		int cur = 0;
		for (int i = 30; ~i; i--) {
			int d = ((num & (1 << i)) != 0);
			if (!nxt[cur][d]) nxt[cur][d] = ++cnt;
			cur = nxt[cur][d];
		}
		return;
	}

	int query(int num) {
		int cur = 0, res = 0;
		for (int i = 30; ~i; i--) {
			int d = ((num & (1 << i)) != 0);
			if (nxt[cur][d ^ 1]) cur = nxt[cur][d ^ 1], res += (1 << i);
			else cur = nxt[cur][d];
		}
		return res;
	}
} trie;
int n, sum[N], ans;
vector<Edge> e[N];

inline void add(int u, int v, int w) {
	return (void) (e[u].emplace_back(v, w));
}

void dfs(int u, int from) {
	for (auto i : e[u]) {
		int v = i.first, w = i.second;
		if (v == from) continue;
		sum[v] = sum[u] ^ w, dfs(v, u);
	}
	return;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	
	cin >> n;
	for (int i = 1, u, v, w; i < n; i++) 
		cin >> u >> v >> w, add(u, v, w), add(v, u, w);

	dfs(1, 0);
	for (int i = 1; i <= n; i++) trie.insert(sum[i]);

	for (int i = 1; i <= n; i++) 
		ans = max(ans, trie.query(sum[i])), cerr << trie.query(sum[i]) << '\n';

	cout << ans << '\n';
	return 0;
}
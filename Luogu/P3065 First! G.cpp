/**
 * @file 	P3065 First! G.cpp
 * @author 	ForgotDream
 * @brief 	Trie + Topo
 * @date 	2023-02-02
 */

#include <bits/stdc++.h>

using namespace std;
using i64 = long long;
using i64u = unsigned long long;
using i128 = __int128;

static const int N = 3e4 + 50, M = 3e5 + 50;
int n;
string str[N];
vector<int> e[26];
int in[26];
bool flg;
vector<string> ans;

inline void add(int u, int v) {
	return (void) (e[u].push_back(v));
}

inline void init() {
	flg = false;
	fill(in, in + 26, 0);
	for (int i = 0; i < 26; i++) e[i].clear();
	return;
}

struct Trie {
	int cnt, nxt[M][26], end[M];

	void insert(string s) {
		int cur = 0;
		for (int i = 0; i < s.length(); i++) {
			if (!nxt[cur][s[i] - 'a']) nxt[cur][s[i] - 'a'] = ++cnt;
			cur = nxt[cur][s[i] - 'a'];
		}
		end[cur]++;
		return;
	}

	void find(string s) {
		int cur = 0;
		for (int i = 0; i < s.length(); i++) {
			if (end[cur]) flg = true;
			int c = s[i] - 'a';
			for (int i = 0; i < 26; i++) 
				if (i != c && nxt[cur][i]) add(c, i), in[i]++;
			cur = nxt[cur][c];
		}
		return;
	}
} trie;

bool topo() {
	queue<int> q;
	for (int i = 0; i < 26; i++) if (!in[i]) q.push(i);
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		for (int v : e[u]) {
			if (!(--in[v])) q.push(v);
		}
	}
	for (int i = 0; i < 26; i++) if (in[i]) return false;
	return true;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	
	cin >> n;

	for (int i = 1; i <= n; i++) 
		cin >> str[i], trie.insert(str[i]);

	for (int i = 1; i <= n; i++) {
		init(), trie.find(str[i]);
		if (topo() && !flg) ans.push_back(str[i]);
	}

	cout << ans.size() << '\n';
	for (auto s : ans) cout << s << '\n';
	return 0;
}
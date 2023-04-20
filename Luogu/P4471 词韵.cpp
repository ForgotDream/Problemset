/**
 * @file 	P4471 词韵.cpp
 * @author 	ForgotDream
 * @brief 	Trie + DP
 * @date 	2023-02-02
 */

#include <bits/stdc++.h>

using namespace std;
using i64 = long long;
using i64u = unsigned long long;
using i128 = __int128;

static const int N = 1e6 + 50;
int n, ans;
string str;
struct Trie {
	int nxt[N][26], cnt;
	int end[N];

	void insert(string s) {
		int cur = 0;
		for (int i = 0; i < s.length(); i++) {
			if (!nxt[cur][s[i] - 'a']) nxt[cur][s[i] - 'a'] = ++cnt;
			cur = nxt[cur][s[i] - 'a'];
		}
		end[cur]++;
		return;
	}
} trie;
int siz[N];

void calc() {	// 根据下标的单调性而避免使用递归
	for (int i = trie.cnt; ~i; i--) {
		siz[i] = trie.end[i];
		int maxx = 0, semi = 0;
		for (int j = 0; j < 26; j++) {
			int v = trie.nxt[i][j];
			if (!trie.end[v]) continue;
			siz[i]++;
			if (siz[v] - 1 > maxx) semi = maxx, maxx = siz[v] - 1;
			else if (siz[v] - 1 > semi) semi = siz[v] - 1;
		}
		siz[i] += maxx, ans = max(ans, siz[i] + semi);
	}
	return;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

	cin >> n;

	for (int i = 1; i <= n; i++) {
		string tmp;
		cin >> tmp, reverse(tmp.begin(), tmp.end());
		trie.insert(tmp);
	}

	calc();

	cout << ans << '\n';
	return 0;
}
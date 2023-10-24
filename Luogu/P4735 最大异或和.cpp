/**
 * @file 	P4735 最大异或和.cpp
 * @author 	ForgotDream
 * @brief 	Persistant 01 Trie
 * @date 	2023-02-03
 */

#include <bits/stdc++.h>

using namespace std;
using i64 = long long;
using i64u = unsigned long long;
using i128 = __int128;

static const int N = 6e5 + 50, DELTA = 1 << 5;
int sum[N], a[N], n, q;
struct Trie {
	int nxt[N * DELTA][2], root[N], val[N * DELTA], cnt;

	void insert(int cur, int lst, int num) {
		for (int i = 27; ~i; i--) {
			val[cur] = val[lst] + 1;
			if (num & (1 << i)) {
				if (!nxt[cur][1]) nxt[cur][1] = ++cnt;
				nxt[cur][0] = nxt[lst][0];
				cur = nxt[cur][1], lst = nxt[lst][1];
			} else {
				if (!nxt[cur][0]) nxt[cur][0] = ++cnt;
				nxt[cur][1] = nxt[lst][1];
				cur = nxt[cur][0], lst = nxt[lst][0];
			}
		}
		val[cur] = val[lst] + 1;
		return;
	}

	int query(int l, int r, int num) {
		int res = 0;
		for (int i = 27; ~i; i--) {
			int t = (num & (1 << i)) ? 1 : 0;
			if (val[nxt[l][t ^ 1]] != val[nxt[r][t ^ 1]]) {
				res += (1 << i); 
				l = nxt[l][t ^ 1], r = nxt[r][t ^ 1];
			} else l = nxt[l][t], r = nxt[r][t];
		}
		return res;
	}
} trie;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

	cin >> n >> q;
	for (int i = 1; i <= n; i++) 
		cin >> a[i], sum[i] = sum[i - 1] ^ a[i];

	for (int i = 1; i <= n; i++) 
		trie.root[i] = ++trie.cnt, trie.insert(trie.root[i], trie.root[i - 1], sum[i]);

	while (q--) {
		char opt[5];
		int l, r, x;
		cin >> opt;
		if (opt[0] == 'A') {
			cin >> x, ++n, sum[n] = sum[n - 1] ^ x;
			trie.root[n] = ++trie.cnt; 
			trie.insert(trie.root[n], trie.root[n - 1], sum[n]);
		} else {
			cin >> l >> r >> x;
			l--, r--;
			if (!l) cout << max(sum[n] ^ x, trie.query(trie.root[r], trie.root[0], sum[n] ^ x)) << '\n';
			else cout << trie.query(trie.root[r], trie.root[l - 1], sum[n] ^ x) << '\n';
		}
	}
	return 0;
}
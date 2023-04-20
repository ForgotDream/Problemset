/**
 * @file 	P3879 阅读理解.cpp
 * @author 	ForgotDream
 * @brief 	Trie
 * @date 	2023-02-02
 */

#include <bits/stdc++.h>

using namespace std;
using i64 = long long;
using i64u = unsigned long long;
using i128 = __int128;

static const int L = 5e3 + 50, N = 1e3 + 50;
vector<vector<int>> pool;
int cnt;
bool isEnd[L * N];
struct Trie {
	int root;

	void insert(string s) {
		int cur = root;
		for (int i = 0; i < s.length(); i++) {
			if (!pool[cur][s[i] - 'a']) {
				vector<int> tmp(26, 0);
				pool.push_back(tmp);
				pool[cur][s[i] - 'a'] = cnt++;
			}
			cur = pool[cur][s[i] - 'a'];
		}
		isEnd[cur] = true;
		return;
	}

	bool find(string s) {
		int cur = root;
		for (int i = 0; i < s.length(); i++) {
			if (!pool[cur][s[i] - 'a']) return false;
			cur = pool[cur][s[i] - 'a'];
		}
		return isEnd[cur];
	}
} t[N];
int n, l, m;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> l, t[i].root = cnt++;
		vector<int> tm(26, 0);
		pool.push_back(tm);
		string tmp;
		while (l--) cin >> tmp, t[i].insert(tmp);
	}

	cin >> m;
	while (m--) {
		string tmp;
		cin >> tmp;
		for (int i = 1; i < n; i++) if (t[i].find(tmp)) cout << i << ' ';
		if (t[n].find(tmp)) cout << n;
		cout << '\n';
	}
	return 0;
}
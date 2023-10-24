/**
 * @file 	P3808 AC 自动机（简单版）.cpp
 * @author 	ForgotDream
 * @brief 	Aho-Corasick Automaton
 * @date 	2023-02-02
 */

#include <bits/stdc++.h>

using namespace std;
using i64 = long long;
using i64u = unsigned long long;
using i128 = __int128;
using Edge = pair<int, int>;

static const int N = 1e6 + 50, M = 1e6 + 50;
template<int M>
struct AhoCorasickAutomaton {
	int cnt, nxt[M][26], fail[M], end[M];

	void insert(string s) {
		int cur = 0;
		for (int i = 0; i < s.length(); i++) {
			if (!nxt[cur][s[i] - 'a']) nxt[cur][s[i] - 'a'] = ++cnt;
			cur = nxt[cur][s[i] - 'a'];
		}
		end[cur]++;
		return;
	}

	void init() {
		static queue<int> q;
		for (int i = 0; i < 26; i++) 
			if (nxt[0][i]) fail[nxt[0][i]] = 0, q.push(nxt[0][i]);
		while (!q.empty()) {
			int u = q.front();
			q.pop();
			for (int i = 0; i < 26; i++) {
				int &t = nxt[u][i];
				if (t) fail[t] = nxt[fail[u]][i], q.push(t);
				else t = nxt[fail[u]][i];
			}
		}
		return;
	}

	int run(string t) {
		int res = 0, cur = 0;
		for (int i = 0; i < t.length(); i++) {
			cur = nxt[cur][t[i] - 'a'];
			for (int j = cur; j && end[j] != -1; j = fail[j]) 
				res += end[j], end[j] = -1;
		}
		return res;
	}
};
AhoCorasickAutomaton<M> acam;
int n;
string str;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	
	cin >> n;
	while (n--) cin >> str, acam.insert(str);
	cin >> str;

	acam.init();
	// for (int i = 1; i <= acam.cnt; i++) cerr << acam.fail[i] << ' ';

	cout << acam.run(str) << '\n';
	return 0;
}
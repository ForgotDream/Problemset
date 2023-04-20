/**
 * @file 	P3121 Censoring G.cpp
 * @author 	ForgotDream
 * @brief 	Aho-Corasick Automaton + Stack
 * @date 	2023-02-02
 */

#include <bits/stdc++.h>

using namespace std;
using i64 = long long;
using i64u = unsigned long long;
using i128 = __int128;
using Edge = pair<int, int>;

static const int N = 1e5 + 50, M = 2e5 + 50;
template<int M>
struct AhoCorasickAutomaton {
	int cnt, nxt[M][26], fail[M], len[M];

	void insert(string s) {
		int cur = 0;
		for (int i = 0; i < s.length(); i++) {
			if (!nxt[cur][s[i] - 'a']) nxt[cur][s[i] - 'a'] = ++cnt;
			cur = nxt[cur][s[i] - 'a'];
		}
		len[cur] = s.length();
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

	string run(string t) {
		string res = "";
		int top = 0;
		vector<int> ans(M, 0), bucket(M, 0);
		int cur = 0;
		for (int i = 0; i < t.length(); i++) {
			bucket[i] = cur = nxt[cur][t[i] - 'a'], ans[++top] = i;
			if (len[cur]) top -= len[cur], cur = bucket[ans[top]];
		}
		for (int i = 1; i <= top; i++) res += t[ans[i]];
		return res;
	}
};
AhoCorasickAutomaton<M> acam;
string s, t;
int n;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	
	cin >> s >> n;
	for (int i = 1; i <= n; i++) cin >> t, acam.insert(t);

	acam.init();
	cout << acam.run(s) << '\n';
	return 0;
}
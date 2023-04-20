/**
 * @file 	P3796 AC 自动机（加强版）.cpp
 * @author 	ForgotDream
 * @brief 	Aho-Corasik Automaton
 * @date 	2023-02-02
 */

#include <bits/stdc++.h>

using namespace std;
using i64 = long long;
using i64u = unsigned long long;
using i128 = __int128;
using Edge = pair<int, int>;

static const int N = 200, M = 1e6 + 50;

struct Result {
	string s;
	int pos, time, to;
	bool operator< (const Result &oth) const {
		if (time == oth.time) return pos < oth.pos;
		return time > oth.time;
	}
} res[N];

template<int M>
struct AhoCorasickAutomaton {
	int cnt, nxt[M][26], fail[M], end[M];
	int d[M];

	void clear() {
		cnt = 0;
		memset(d, 0, sizeof d);
		memset(nxt, 0, sizeof nxt);
		memset(end, 0, sizeof end);
		return;
	}

	int insert(string s) {
		int cur = 0;
		for (int i = 0; i < s.length(); i++) {
			if (!nxt[cur][s[i] - 'a']) nxt[cur][s[i] - 'a'] = ++cnt;
			cur = nxt[cur][s[i] - 'a'];
		}
		end[cur]++;
		return cur;
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
			for (int j = cur; j; j = fail[j]) 
				res += end[j], d[j]++;
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
	
	while (cin >> n && n) {
		acam.clear();
		for (int i = 1; i <= n; i++) {
			cin >> str; 
			res[i].pos = i, res[i].time = 0; 
			res[i].s = str, res[i].to = acam.insert(str);
		}

		acam.init();
		cin >> str, acam.run(str);
		for (int i = 1; i <= n; i++) res[i].time = acam.d[res[i].to];

		sort(res + 1, res + n + 1);
		cout << res[1].time << '\n' << res[1].s << '\n';
		for (int i = 2; i <= n; i++) 
			if (res[i].time == res[1].time) cout << res[i].s << '\n';
			else break;
	}
	return 0;
}
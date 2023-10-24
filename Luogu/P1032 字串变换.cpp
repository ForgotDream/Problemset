/**
 * @file    P1032 字串变换.cpp
 * @author  ForgotDream
 * @brief   BFS
 * @date    2023-02-11
 */
#include <bits/stdc++.h>
#include <unordered_map>

using namespace std;
using i64 = long long;
using i128 = __int128;

static const int N = 1e3 + 50;
map<string, int> dis;
map<string, vector<string>> rules;
string tgt, dst, x, y;

vector<int> myFind(string s, string p) {
	static vector<int> res;
	res.clear();
	
	for (int i = 0; i < (int) s.length(); i++) {
		int sPivot = i, pPivot = 0;
		while (s[sPivot] == p[pPivot] 
			&& sPivot < (int) s.length() 
			&& pPivot < (int) p.length()) sPivot++, pPivot++;
		if (pPivot == (int) p.length()) res.push_back(i);
	}

	return res;
}

int bfs() {
	static queue<string> q;
	dis[tgt] = 0, q.push(tgt);

	if (tgt == dst) return 0;

	while (!q.empty()) {
		auto u = q.front();
		q.pop();

		for (auto rule : rules) {
			string curRule = rule.first, lst = u;
			auto s = myFind(u, curRule);
			for (int i : s) {
				for (auto str : rule.second) {
					lst = u;
					lst.replace(i, curRule.length(), str);

					// cerr << u << ' ' << lst << ' ' << str << '\n';

					if (dis.count(lst)) continue;
					dis[lst] = dis[u] + 1;

					if (lst == dst) return dis[lst];
					else if (dis[lst] > 10) return -1;
					else q.push(lst);
				}
			}
		}
	}

	return -1;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

	cin >> tgt >> dst;
	while (cin >> x >> y) 
		cerr << x << ' ' << y << '\n', rules[x].push_back(y);

	int res = bfs();
	if (~res) cout << res << '\n';
	else cout << "NO ANSWER!" << '\n';

	return 0;
}
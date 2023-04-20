/**
 * @file 	P4683 Type Printer.cpp
 * @author 	ForgotDream
 * @brief 	Trie + DFS
 * @date 	2023-02-03
 */

#include <bits/stdc++.h>

using namespace std;
using i64 = long long;
using i64u = unsigned long long;
using i128 = __int128;
using Edge = pair<int, int>;

static const int N = 1e5 + 50;
int all, ans;
struct Trie {
	int cnt;
	// vector<vector<int>> nxt;
	int nxt[5 * N][28];

	// Trie() { nxt.emplace_back(28, 0), cnt = 0; }

	void insert(string s, bool isLongest = false) {
		// cerr << s << ' ' << isLongest << '\n';
		int cur = 0;
		for (int i = 0; i < s.length(); i++) {
			if (!nxt[cur][s[i] - 'a']) {
				// nxt.emplace_back(28, 0);
				nxt[cur][s[i] - 'a'] = ++cnt;
			}
			cur = nxt[cur][s[i] - 'a'], nxt[cur][26] = nxt[cur][26] | isLongest;
 		}
		nxt[cur][27]++, all++;
		return;
	}
} trie;
int n, pivot;
string ansSeq, in[N];

void dfs(int cur = 0, int ch = 0) {
	int pivot = -1;
	if (cur != 0) ansSeq += 'a' + ch, ans++;
	while (trie.nxt[cur][27]--) ansSeq += 'P', all--, ans++; 
	for (int i = 0; i < 26; i++) {
		if (trie.nxt[cur][i] && trie.nxt[trie.nxt[cur][i]][26]) {
			// cerr << (char) (i + 'a') << endl;
			pivot = i;
			continue;
		}
		if (trie.nxt[cur][i]) dfs(trie.nxt[cur][i], i);
	}
	if (~pivot) dfs(trie.nxt[cur][pivot], pivot);
	if (all) ansSeq += '-', ans++;
	return;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> in[i];
		if (i == 1) pivot = 1;
		else if (in[pivot].length() < in[i].length()) pivot = i;
	}

	// cerr << pivot << '\n';

	for (int i = 1; i <= n; i++) trie.insert(in[i], pivot == i);
	// cerr << trie.nxt[1][26] << '\n';

	dfs();
	cout << ans << '\n';
	for (char c : ansSeq) cout << c << '\n';
	return 0;
}
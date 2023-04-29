#include <bits/stdc++.h>

using namespace std;

const int N = 5e5 + 50;
int n, ans, e[N];
int chCnt[N];
string s[N];
struct Trie {
	int nxt[N][26], cnt;
	int end[N];

	int insert(string s) {
		int len = s.length(), cur = 0;
		for (int i = 0; i < len; i++) {
			// cerr << i << ' ' << (i == len) << endl;
			int c = s[i] - 'a';
			if (!nxt[cur][c]) nxt[cur][c] = ++cnt;
			// if (cur == 2) cerr << i << endl;
			chCnt[cur]++;
			cur = nxt[cur][c];
		}
		end[cur]++;
		return cur;
	}
} trie;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

	cin >> n;
	for (int i = 1; i <= n; i++) cin >> s[i], e[i] = trie.insert(s[i]);
	
	// for (int i = 0; i <= trie.cnt; i++) cout << chCnt[i] << endl;

	for (int i = 1; i <= n; i++) {
		ans = 0;
		// cerr << '$' << i << ": ";
		int len = s[i].length(), cur = 0;
		for (int j = 0; j < len; j++) {
			cur = trie.nxt[cur][s[i][j] - 'a'];
			// cerr << cur << ' ';
			if ((chCnt[cur] > 1 && cur != e[i]) || (e[i] == cur && (trie.end[i] > 1 || chCnt[cur])) || (trie.end[cur] && e[i] != cur)) 
				ans = max(ans, j + 1);
		}
		// cerr << endl;
		cout << ans << endl;
	}

	// cerr << (e[1] == 11 && (e[1] > 1 || chCnt[11])) << endl;
	// cerr << (e[1] == 11) << ' ' << e[1] << ' ' << chCnt[11] << endl;
	return 0;
}
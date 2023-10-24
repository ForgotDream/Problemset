/**
 * @file    P1155 双栈排序.cpp
 * @author  ForgotDream
 * @brief   栈 + 二分图
 * @date    2023-02-21
 */
#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

static const int N = 1e3 + 50, INF = 0x3f3f3f3f;
int n;
int a[N], minn[N];
int col[N];
vector<int> e[N];
string ans = "";
stack<int> s1, s2;
int tgt, cur;

inline void add(int u, int v) {
	return (void) (e[u].push_back(v));
}

void dfs(int u, int curCol = 1) {
	col[u] = curCol;
	int nxtCol = curCol == 1 ? 2 : 1;
	for (int v : e[u]) {
		if (!col[v]) {
			dfs(v, nxtCol);
		} else if (nxtCol != col[v]) {
			cout << 0 << '\n';
			exit(0);
		}
	}
	return;
}

signed main() {
	ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
	}

	minn[n + 1] = INF;
	for (int i = n; i; i--) {
		minn[i] = min(a[i], minn[i + 1]);
	}
	for (int i = 1; i <= n; i++) {
		for (int j = i + 1; j <= n; j++) {
			if (minn[j + 1] < a[i] && a[i] < a[j]) {
				add(i, j);
				add(j, i);
			}
		}
	}

	for (int i = 1; i <= n; i++) {
		if (!col[i]) {
			dfs(i);
		}
	}

	cur = 1;
	tgt = 1;
	while (tgt <= n) {
		if (col[cur] == 1 && (s1.empty() || s1.top() > a[cur])) {
			s1.push(a[cur]);
			cur++;
			ans += "a ";
		} else if (!s1.empty() && tgt == s1.top()) {
			s1.pop();
			tgt++;
			ans += "b ";
		} else if (col[cur] == 2 && (s2.empty() || s2.top() > a[cur])) {
			s2.push(a[cur]);
			cur++;
			ans += "c ";
		} else if (!s2.empty() && tgt == s2.top()) {
			s2.pop();
			tgt++;
			ans += "d ";
		}

		// cerr << tgt << '\n';
	}

	cout << ans << '\n';

	return 0;
}
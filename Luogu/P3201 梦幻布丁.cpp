/**
 * @file    P3201 梦幻布丁.cpp
 * @author  ForgotDream
 * @brief   启发式合并
 * @date    2023-02-05
 */
#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

static const int N = 1e6 + 5;
vector<int> vec[N];
int n, m, col[N], cur[N];
int ans;

void merge(int x, int y) {
	for (int i : vec[x]) {
		if (col[i - 1] == y) ans--;
		if (col[i + 1] == y) ans--;
	}
	for (int i : vec[x]) col[i] = y, vec[y].push_back(i);
	vec[x].clear();
	return;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		cin >> col[i];
		if (col[i] != col[i - 1]) ans++;
		cur[col[i]] = col[i];
		vec[col[i]].push_back(i);
	}

	for (int i = 1; i <= m; i++) {
		int opt, x, y;
		cin >> opt;
		if (opt == 1) {
			cin >> x >> y;
			if (x == y) continue;
			if (vec[cur[x]].size() > vec[cur[y]].size()) swap(cur[x], cur[y]);
			merge(cur[x], cur[y]);
		} else cout << ans << '\n';
	}
	return 0;
}
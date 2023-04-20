#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using Edge = pair<int, int>;

const int N = 1e5 + 50, M = 20, INF = 0x3f3f3f3f;
int n, m, belong[N], f[1 << M];
int num[N], sum[M][N];

void solve() {
	memset(f, 0x3f, sizeof f), f[0] = 0;
	for (int i = 1; i <= (1 << m) - 1; i++) {
		int len = 0;
		for (int j = 0; j < m; j++) if (i & (1 << j)) len += num[j];
		// cerr << len << endl;
		for (int j = 0; j < m; j++)
			if (i & (1 << j))
				f[i] = min(f[i], f[i ^ (1 << j)] + num[j] - (sum[j][len] - sum[j][len - num[j]]));
	}
	cout << f[(1 << m) - 1] << endl;
	return;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		cin >> belong[i], belong[i]--, num[belong[i]]++;
		for (int j = 0; j < m; j++) sum[j][i] = sum[j][i - 1];
		sum[belong[i]][i]++;
	}
	/*
	for (int i = 0; i < m; i++) {
		cerr << i << ": ";
		for (int j = 1; j <= n; j++) 
			cerr << sum[i][j] << ' ';
		cerr << endl;
	}
	*/
	solve();
	return 0;
}
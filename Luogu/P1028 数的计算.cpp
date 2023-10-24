/**
 * @file    P1028 数的计算.cpp
 * @author  ForgotDream
 * @brief   递推 + 记忆化搜索
 * @date    2023-02-11
 */
#include <bits/stdc++.h>

using namespace std;
using i64 = long long;
using i128 = __int128;

static const int N = 1e3 + 50;
int f[N][N], n;

int dfs(int cur = n, int length = 1) {
	int res = 1;
	if (cur == 1) return res;
	if (f[cur][length]) return f[cur][length];
	for (int i = cur / 2; i; i--) {
		res += dfs(i, length + 1);
	}
	return f[cur][length] = res;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

	cin >> n;
	cout << dfs() << '\n';
	return 0;
}
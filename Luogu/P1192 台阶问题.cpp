/**
 * @file    P1192 台阶问题.cpp
 * @author  ForgotDream
 * @brief   递推
 * @date    2023-02-14
 */
#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

static const int N = 1e5 + 50, MOD = 1e5 + 3;
int n, k;
int f[N];

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	
	cin >> n >> k;

	f[0] = 1;
	for (int i = 1; i <= n; i++) 
		for (int j = k; j; j--) 
			if (i >= j) (f[i] += f[i - j]) %= MOD;

	cout << f[n] << '\n'; 

	return 0;
}
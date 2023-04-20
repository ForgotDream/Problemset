/**
 * @file    UVA11762 Race to 1.cpp
 * @author  ForgotDream
 * @brief   记忆化搜索
 * @date    2023-02-19
 */
#include <algorithm>
#include <bits/stdc++.h>
#include <iomanip>

using namespace std;
using i64 = long long;

static const int N = 1e6 + 50;
int T;
int primeCnt, prime[N];
bool isNotPrime[N], vis[N];
double f[N];

void getPrime(int n) {
	for (int i = 2; i <= n; i++) {
		if (!isNotPrime[i]) prime[++primeCnt] = i;
		for (int j = 1; j <= primeCnt && (i64) i * prime[j] <= n; j++) {
			isNotPrime[i * prime[j]] = true;
			if (!(i % prime[j])) break;
		}
	}
}

double solve(int num) {
	if (num == 1) return 0;
	if (vis[num]) return f[num];
	vis[num] = true;
	int fact = 0, cnt = 0;
	for (int i = 1; i <= primeCnt && prime[i] <= num; i++) {
		cnt++;
		if (!(num % prime[i])) {
			fact++;
			f[num] += solve(num / prime[i]);
		}
	}
	return f[num] = (f[num] + cnt) / fact;
}

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

	getPrime(1e6);

	cin >> T;
	for (int t = 1; t <= T; t++) {
		int num;
		cin >> num;
		cout << "Case " << t << ": " << fixed << setprecision(10) << solve(num) << '\n';
	}

	return 0;
}
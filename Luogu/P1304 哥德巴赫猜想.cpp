/**
 * @file    P1304 哥德巴赫猜想.cpp
 * @author  ForgotDream
 * @brief   质数筛
 * @date    2023-02-23
 */
#include <bits/stdc++.h>
#include <iomanip>

using namespace std;
using i64 = long long;

static const int N = 1e4 + 50, INF = 0x3f3f3f3f;
int cnt, prime[N];
bool isNotPrime[N];
int n;

void getPrime(int n) {
	for (int i = 2; i <= n; i++) {
		if (!isNotPrime[i]) prime[++cnt] = i;
		for (int j = 1; j <= cnt && (i64) i * prime[j] <= n; j++) {
			isNotPrime[i * prime[j]] = true;
			if (!(i % prime[j])) break;
		}
	}
	return;
}

signed main() {
	ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

	getPrime(1e4);

	cin >> n;
	
	for (int i = 4; i <= n; i += 2) {
		for (int j = 1; j <= cnt && prime[j] <= i; j++) {
			if (!isNotPrime[i - prime[j]]) {
				cout << i << "=" << prime[j] << "+" << i - prime[j] << '\n';
				break;
			}
		}
	}

	return 0;
}
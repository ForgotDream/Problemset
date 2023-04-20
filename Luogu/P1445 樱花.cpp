/**
 * @file 	P1445 樱花.cpp
 * @author 	ForgotDream
 * @brief 	唯一分解定理 + 因式分解
 * @date 	2023-01-31
 */

#include <bits/stdc++.h>

namespace FastIO {
	template<typename T>
	inline void read(T& x) {
		x = 0;
		T f = 1;
		char c = getchar();
		while (!isdigit(c)) {
			if (c == '-') f = -1;
			c = getchar();
		}
		while (isdigit(c)) x = x * 10 + c - '0', c = getchar();
		x *= f;
		return;
	}

	template<typename T, typename ... args>
	inline void read(T& x, args& ... tmp) {
		read(x);
		read(tmp...);
		return;
	}

	template<typename T>
	inline void print(T x) {
		if (x < 0) putchar('-'), x = -x;
		if (x / 10) print(x / 10);
		putchar(x % 10 + '0');
		return;
	}

	template<typename T>
	inline void print(T x, char c) {
		print(x), putchar(c);
		return;
	}
}

using namespace std;
using namespace FastIO;
using i64 = long long;
using i64u = unsigned long long;
using i128 = __int128;

static const int N = 1e6 + 50, MOD = 1e9 + 7;
int n;
int cnt, prime[N];
bool isNotPrime[N];
i128 a[N], ans = 1;

void getPrime(int n) {
	isNotPrime[1] = true;
	for (int i = 2; i <= n; i++) {
		if (!isNotPrime[i]) prime[++cnt] = i;
		for (int j = 1; j <= cnt && (i64) prime[j] * i <= n; j++) {
			isNotPrime[i * prime[j]] = true;
			if (!(i % prime[j])) break;
		}
	}
	return;
}

int main() {
	read(n), getPrime(n);

	for (int i = 1; i <= cnt; i++) 
		for (i128 j = prime[i]; j <= n; j *= prime[i]) 
			a[i] = (a[i] + n / j) % MOD;

	for (int i = 1; i <= cnt; i++)
		ans = (ans * (2 * a[i] + 1)) % MOD;

	print(ans, '\n'); 
	return 0;
}
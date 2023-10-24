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
using i128 = __int128;

const int N = 250, M = 1e6 + 50;
int k;
int n[N], m[N];
int cnt, prime[M], primeCnt[M];
bool isNotPrime[M];
double ans = 1;

void getPrime(int n) {
	for (int i = 2; i <= n; i++) {
		if (!isNotPrime[i]) prime[++cnt] = i;
		for (int j = 1; j <= cnt && (i64) i * prime[j] <= n; j++) {
			isNotPrime[i * prime[j]] = true;
			if (!(i % prime[j])) break;
		}
	}
}

void divide(int num, int d) {
	int cur = 1;
	while (num != 1) {
		while (!(num % prime[cur])) num /= prime[cur], primeCnt[cur] += d;
		cur++;
	}
	return;
}

int main() {
	getPrime(1e6);

	read(k);
	for (int i = 1; i <= k; i++) read(n[i]), divide(n[i], 1);
	for (int i = 1; i <= k; i++) read(m[i]), divide(m[i], -1);

	for (int i = 1; i <= cnt; i++) {
		for (int j = 1; j <= abs(primeCnt[i]); j++)
			if (primeCnt[i] > 0) ans *= (double) prime[i];
			else ans /= (double) prime[i];
	}

	printf("%.5lf\n", ans);
	// cout << 
	return 0;
}

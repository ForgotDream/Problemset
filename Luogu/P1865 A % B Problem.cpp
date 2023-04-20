#include <algorithm>
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

const int M = 1e6 + 50;
int n, m;
int cnt, prime[M], primeCnt[M];
bool isNotPrime[M];

void getPrime(int n) {
	for (int i = 2; i <= n; i++) {
		if (!isNotPrime[i]) prime[++cnt] = i;
		for (int j = 1; j <= cnt && (i64) i * prime[j] <= n; j++) {
			isNotPrime[i * prime[j]] = true;
			if (!(i % prime[j])) break;
		}
	}
}

int main() {
	read(n, m);

	getPrime(m);

	for (int i = 1; i <= n; i++) {
		int l, r;
		read(l, r);
		if (!(1 <= l && r <= m)) {
			printf("Crossing the line\n");
			continue;
		}
		int ans = upper_bound(prime + 1, prime + cnt + 1, r) - lower_bound(prime + 1, prime + cnt + 1, l);
		print(ans, '\n');
	}
	return 0;
}

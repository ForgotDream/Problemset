/**
 * @file P2563 质数和分解.cpp
 * @author ForgotDream
 * @brief 数学基础 + 完全背包
 * @date 2023-01-29
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

const int N = 1e5 + 50;
int n;
int prime[N], cnt;
bool vis[N];
int f[N];

void getPrime(int n) {
	for (int i = 2; i <= n; i++) {
		if (vis[i]) continue;
		prime[++cnt] = i;
		for (int j = i * i; j <= n; j += i) vis[j] = true;
	}
	return;
}

int main() {
	getPrime(200);
	
	// for (int i = 1; i <= cnt; i++) cerr << prime[i] << ' ';

	f[0] = 1;
	for (int j = 1; j <= cnt; j++)
		for (int i = prime[j]; i <= 200; i++)
			f[i] += f[i - prime[j]]; 

	while (cin >> n) cout << f[n] << endl;
	return 0;
}

/**
 * @file P2926 Patting Heads S.cpp
 * @author ForgotDream
 * @brief 数学基础，时间复杂度 O(n * H(n))
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

const int N = 1e5 + 50, M = 1e6 + 50;
int n, maxx;
int bucket[M], a[N], res[M];

int main() {
	read(n);
	for (int i = 1; i <= n; i++) 
		read(a[i]), bucket[a[i]]++, maxx = max(maxx, a[i]);

	for (int i = 1; i <= maxx; i++)
		if (bucket[i])
			for (int j = 1; j * i <= maxx; j++)
				res[j * i] += bucket[i];

	for (int i = 1; i <= n; i++)
		print(res[a[i]] - 1, '\n');
	return 0;
}

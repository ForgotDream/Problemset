/**
 * @file 	P4391 Radio Transmission.cpp
 * @author 	ForgotDream
 * @brief 	KMP
 * @date 	2023-02-01
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

const int N = 1e6 + 50;
int n, fail[N];
char s[N];

void init() {
	int i = 0, j = -1;
	fail[0] = -1;
	while (i < n && j < n) {
		if (j == -1 || s[i] == s[j]) fail[++i] = ++j;
		else j = fail[j];
	}
	return;
}

int main() {
	read(n);
	scanf("%s", s);
	
	init();

	print(n - fail[n], '\n');
	return 0;
}
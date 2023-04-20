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

const int M = 1e6 + 50;
int n;
int cnt, col[M];

void getPrime(int n) {
	for (int i = 2; i <= n; i++) {
		if (col[i]) continue;
		for (i64 j = (i64) i * i; j <= n; j += i) 
			col[j] = 1;
	}
	return;
}

int main() {
	read(n);
	
	print(1 + (n >= 3), '\n');
	getPrime(n + 1);

	for (int i = 2; i <= n + 1; i++) print(col[i] + 1, ' ');
	return 0;
}

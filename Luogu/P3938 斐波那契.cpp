#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;
using ll = long long;

int m;
ll a, b;
ll fib[100];

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

inline void init() {
	fib[0] = fib[1] = 1;
	for (int i = 2; i <= 61; i++) fib[i] = fib[i - 1] + fib[i - 2];
	return;
}

inline void solve(ll a, ll b) {
	if (a < b) swap(a, b);
	if (a == b) return (void)(printf("%lld\n", a));
	int lb = lower_bound(fib, fib + 62, a) - fib;
	solve(b, a - fib[lb - 1]);
	return;
}

int main() {
	read(m);
	init();
	while (m--) {
		read(a, b);
		solve(a, b);
	}
	return 0;
}
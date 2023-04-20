#include <bits/stdc++.h>
#include <cstdint>

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
using ll = long long;
using ull = unsigned long long;
using i128 = __int128;

const int N = 1e6 + 50;
int n, cnt;
i128 tree[N], ans, a[N], b[N];

inline int lowbit(int x) {
	return x & -x;
}

void add(int x, i128 num) {
	for (int i = x; i <= n; i += lowbit(i))
		tree[i] += num;
	return;
}

i128 query(int x) {
	i128 res = 0;
	for (int i = x; i; i -= lowbit(i)) res += tree[i];
	return res;
}

int main() {
	read(n);
	for (int i = 1; i <= n; i++) read(a[i]), b[i] = a[i];
	
	sort(b + 1, b + n + 1);
	cnt = unique(b + 1, b + n + 1) - b - 1;

	for (int i = 1; i <= n; i++) a[i] = lower_bound(b + 1, b + cnt + 1, a[i]) - b;

	for (int i = n; i; i--) 
		ans += query(a[i] - 1) * i, add(a[i], n - i + 1);

	print(ans, '\n');
	return 0;
}

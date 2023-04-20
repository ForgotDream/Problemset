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
using ll = long long;
using ull = unsigned long long;

const int N = 5e5 + 50;
int n, type, D;
int a[N];
ll tree[N][3], ans;
vector<int> bucket[N];

inline int lowbit(int x) {
	return x & -x;
}

ll sum(int x) {
	ll res = 0;
	for (int i = x; i; i -= lowbit(i)) 
		res += tree[i][0] * (x + 2) * (x + 1) - tree[i][1] * (2 * x + 3) + tree[i][2];
	return res / 2;
}

void add(int x, ll num) {
	for (int i = x; i <= 2 * n + 1; i += lowbit(i))
		tree[i][0] += num, tree[i][1] += num * x, tree[i][2] += num * x * x;
	return;
}

int main() {
	read(n, type), D = n + 1;
	for (int i = 1; i <= n; i++) read(a[i]), bucket[a[i]].push_back(i);

	for (int i = 0; i < n; i++) {
		bucket[i].push_back(n + 1);
		int pivot = 0;
		for (int j = 0; j < bucket[i].size(); j++) {
			int y = 2 * j - pivot + D, x = 2 * j - (bucket[i][j] - 1) + D;
			ans += sum(y - 1) - (x >= 3 ? sum(x - 2) : 0);
			add(x, 1), add(y + 1, -1);
			pivot = bucket[i][j];
		}
		pivot = 0;
		for (int j = 0; j < bucket[i].size(); j++) {
			int y = 2 * j - pivot + D, x = 2 * j - (bucket[i][j] - 1) + D;
			add(x, -1), add(y + 1, 1);
			pivot = bucket[i][j];
		}
	}

	print(ans, '\n');
	return 0;
}

#include <bits/stdc++.h>

namespace FastIO {
	char buf[1 << 23], *p1 = buf, *p2 = buf;

	inline char gc() {
		return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 23, stdin), p1 == p2) ? EOF : *p1++;
	}

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

// 组合意义天地灭，代数推导保平安！
// 自己能写出的最低时间复杂度：O(n ^ 2 log n)
// 应该的时间复杂度：O(n ^ 2)
// 现在我真不知道正解复杂度是多少。。。一车人写 O(n ^ 3) 过了。。。

using namespace std;
using namespace FastIO;
using ll = long long;

const int N = 1.5e3 + 50;
ll n, a[N], b[N], c[N], sum[N];

void solve() {
	ll res = 0;
	for (int j = 2; j < n; j++) {
		// 预处理 i
		for (int i = 1; i < j; i++) b[i] = a[i] + j - i;
		sort(b + 1, b + j);

		// 预处理 k
		for (int k = j + 1; k <= n; k++) c[k] = a[k] + k - j;
		sort(c + j + 1, c + n + 1), c[j] = a[j];
		for (int k = j + 1; k <= n; k++) sum[k] = sum[k - 1] + c[k];

		// 查找临界点
		int pivot1 = upper_bound(b + 1, b + j, a[j]) - b;
		int pivot2 = upper_bound(c + j + 1, c + n + 1, a[j]) - c;
		
		for (int i = 1; i < j; i++) {
			if (i < pivot1) {
				res += (sum[n] - sum[pivot2 - 1]) + a[j] * (pivot2 - j - 1);
				// res += a[j] * (n - pivot2 + 1) + (sum[pivot2 - 1] - sum[j + 1]);
			}
			else {
				int pivot3 = upper_bound(c + j + 1, c + n + 1, b[i]) - c;
				res += b[i] * (pivot3 - j - 1) + (sum[n] - sum[pivot3 - 1]);
				// res += b[i] * (n - pivot3 + 1) + (sum[pivot3 - 1] - sum[j + 1]);
			}
		}
	}
	print(res, '\n');
	return;
}

int main() {
	read(n);
	for (int i = 1; i <= n; i++) read(a[i]);
	solve();
	return 0;
}

/**
 * @file 	P3501 ANT-Antisymmetry.cpp
 * @author 	ForgotDream
 * @brief 	Manacher
 * @date 	2023-02-01
 */

#include <bits/stdc++.h>
#include <random>

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

static const int N = 5e5 + 50;
int n, cnt;
char raw[N], str[2 * N], rev[2 * N];
i64 ans, d[2 * N];

int main() {
	read(n), scanf("%s", raw + 1);
	
	for (int i = 1; i <= n; i++) {
		++cnt, str[cnt] = rev[cnt] = '$';
		++cnt, str[cnt] = raw[i], rev[cnt] = (raw[i] - '0') ^ 1 + '0';
	}
	str[0] = rev[0] = '{', str[cnt + 1] = rev[cnt + 1] = '}';

	for (int i = 1, mid = 0, r = 0; i <= cnt; i += 2) {
		d[i] = (i < r) ? min(d[(mid << 1) - i], d[mid] + mid - i) : 1;
		while (str[i + d[i]] == rev[i - d[i]]) d[i]++;
		if (d[i] + i > r) r = d[i] + i, mid = i;
		ans += (d[i] >> 1);
	}

	print(ans, '\n');
	return 0;
}
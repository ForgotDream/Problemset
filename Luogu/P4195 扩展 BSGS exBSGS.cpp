/**
 * @file 	P4195 扩展 BSGS/exBSGS.cpp
 * @author 	ForgotDream
 * @brief 	exGCD + BSGS = exBSGS
 * @date 	2023-02-01
 */

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/hash_policy.hpp>

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
using namespace __gnu_pbds;
using i64 = long long;
using i64u = unsigned long long;
using i128 = __int128;

static const int N = 1e6 + 50, MOD = 1e9 + 7;
int n, m, p;
gp_hash_table<int, int> mp;
int x, y;

int exgcd(int a, int b, int &x, int &y) {
	if (!b) return x = 1, y = 0, a;
	int res = exgcd(b, a % b, y, x);
	return y -= a / b * x, res;
}

int exBSGS(int base, int rst, int mod) {
	base %= mod, rst %= mod;
	if (mod == 1 || rst == 1) return 0;
	int tmp, A = 1, cnt = 0;
	while ((tmp = exgcd(base, mod, x, y)) != 1) {   // 是否可以写成递归形式
		if (rst % tmp) return -1;
		rst /= tmp, mod /= tmp, ++cnt;
		A = (i64) A * (base / tmp) % mod;
		if (A == rst) return cnt;
	}

	// cerr << cnt << '\n';

	exgcd(A, mod, x, y);
	int inv = (x % mod + mod) % mod;
	rst = (i64) rst * inv % mod;

	// cerr << 1 << '\n';

	mp.clear();

	int t = ceil(sqrt(mod));
	i64 cur = 1;
	for (int i = 0; i < t; i++) 
		mp[(i64) rst * cur % mod] = i, cur = (i64) cur * base % mod;
	i64 now = cur;
	if (!now) return !rst ? 1 + cnt : -1;

	// cerr << 1 << '\n';

	/*
	cerr << t << '\n';
	for (auto it : mp) 
		cerr << it.first << ' ' << it.second << '\n';
	*/

	for (int i = 0; i <= t; i++) {
		// cerr << now << '\n';
		int k = mp.find(now) == mp.end() ? -1 : mp[now];
		if (~k) return /* cerr << i << ' ' << mp[now] << endl, */ (i + 1) * t - mp[now] + cnt;
		now = now * cur % mod;
	}

	return -1;
}

int main() {
	while (read(n, p, m), n && p && m) {
		int ans = exBSGS(n, m, p);
		if (!(~ans)) printf("No Solution\n");
		else print(ans, '\n');
	} 
	return 0;
}
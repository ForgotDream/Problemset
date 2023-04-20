/**
 * @file 	P2375 动物园.cpp
 * @author 	ForgotDream
 * @brief 	KMP + ????
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

const int L = 1e6 + 50, MOD = 1e9 + 7;
int n, fail[L], num[L], ans, num2[L];
char str[L];
int f[L], len;
vector<int> vec[L];

int calc(int i, int from) {
	if (!i) return f[i] = 0;
	// if (f[i] && i != from) return f[i];
	return f[i] = (2 * fail[i] <= from && fail[i]) + calc(fail[i], from);
}

void init() {
	// memset(t, 0, sizeof t);
	int i = 0, j = -1;
	len = strlen(str);
	fail[0] = -1;
	while (i < len && j < len) {
		if (j == -1 || str[i] == str[j]) fail[++i] = ++j;
		else j = fail[j];
	}

	// for (int i = 1; i <= len; i++) num[i]= calc(i, i);

	/*
	for (int i = 1; i <= len; i++) cerr << fail[i] << ' ';
	cerr << '\n';
	for (int i = 1; i <= len; i++) cerr << num[i] << ' ';
	cerr << '\n';
	*/

	for (int i = 1; i <= len; i++) {
		int res = 0, pre = fail[i];
		while (pre) {
			if (2 * pre <= i) res++;
			pre = fail[pre];
			if (f[pre]) {
				res += f[pre];
				break;
			}
		}
		f[i] = res + 1;
		ans = (i64) ans * (res + 1) % MOD;
	}

	// for (int i = 1; i <= len; i++) ans = (i64) ans * (num[i] + 1) % MOD;
	return;
}

int main() {
	read(n);
	while (n--) {
		ans = 1;
		scanf("%s", str);
		init();
		if (n) print(ans, '\n');
		else print(ans);
	}
	return 0;
}
/**
 * @file 	P5410 扩展 KMP（Z 函数）.cpp
 * @author 	ForgotDream
 * @brief 	exKMP/Z Function
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

const int N = 2e7 + 50;
string a, b, c;
i64 Z[N << 1], z, p;

void getZ(string str) {
	for (int i = 1, l = 0; i < str.length(); i++) {
		if (l + Z[l] > i) Z[i] = min(Z[i - l], l + Z[l] - i);
		while (i + Z[i] < str.length() && str[Z[i]] == str[i + Z[i]]) Z[i]++;
		if (i + Z[i] > l + Z[l]) l = i;
	}
	return;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

	cin >> a >> b;
	// printf("%s\n", c);
	
	getZ(b + a);
	z = b.length() + 1;
	
	for (int i = 1; i < b.length(); i++) 
		z ^= (i64) (min(Z[i], (i64) b.length() - i) + 1) * (i + 1);
	for (int i = 0; i < a.length(); i++) 
		p ^= (i64) (min(Z[i + b.length()], (i64) b.length()) + 1) * (i + 1);

	cout << z << '\n' << p << '\n';
	return 0;
}
#include <iostream>
#include <cstdio>

using namespace std;

typedef __int128 i128;

int t;
i128 ans;
i128 a, b;

inline i128 read() {
	i128 x = 0, f = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9') {
		if (ch == '-')
			f = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9') {
		x = x * 10 + ch - '0';
		ch = getchar();
	}
	return x * f;
}

inline void print(i128 x) {
	if (x < 0) {
		putchar('-');
		x = -x;
	}
	if (x > 9)
		print(x / 10);
	putchar(x % 10 + '0');
}

int main() {
	cin >> t;
	while (t--) {
		a = read(), b = read();
		ans = (b * (b + 1) / 2 - a * (a - 1) / 2) % 9;
		print(ans);
		putchar('\n');
	}
	return 0;
}
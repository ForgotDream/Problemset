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

using namespace std;
using namespace FastIO;
using ll = long long;

const int N = 5050;
char s[N];
ll ans;
int len;

int main() {
	scanf("%s", s + 1), len = strlen(s + 1);

	for (int i = 1; i <= len; i++) ans = ans * 26 + s[i] - 'A' + 1;

	print(ans, '\n');
	return 0;
}
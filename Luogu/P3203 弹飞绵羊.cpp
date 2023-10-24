#include <iostream>
#include <cstdio>
#include <cmath>

using namespace std;

const int N = 2e5 + 50;
int L;
int n, m;
int st[N], opt, cur, new_val;
int step[N], to[N], belong[N], l[N], r[N], cnt;

template<typename T>
void read(T& x) {
	x = 0;
	int f = 1;
	char c = getchar();
	while (!isdigit(c)) f = (f == 1 && c == '-') ? -1 : 1, c = getchar();
	while (isdigit(c)) x = x * 10 + c - '0', c = getchar();
	return;
}

template<typename T, typename ... args>
void read(T& x, args& ... tmp) {
	read(x);
	read(tmp...);
	return;
}

template<typename T>
void print(T x) {
	if (x / 10) print(x / 10);
	putchar(x % 10 + '0');
	return;
}

void init() {
	for (int i = 1; i <= n; i++) {
		belong[i] = (i - 1) / L + 1, cnt = max(cnt, (i - 1) / L + 1);
		if (belong[i] > belong[i - 1]) l[belong[i]] = i, r[belong[i - 1]] = i - 1;
	}
	r[belong[n]] = n;
	// cout << r[belong[1]] << endl;
	for (int i = n; i >= 1; i--) {
		if (i + st[i] > r[belong[i]]) step[i] = 1, to[i] = i + st[i];
		else step[i] = step[i + st[i]] + 1, to[i] = to[i + st[i]];
	}
	// for (int i = 1; i <= n; i++) cout << step[i] << ' ' << to[i] << endl;
	return;
}

int get(int u) {
	u++;
	int res = 0;
	while (u <= n) res += step[u], u = to[u];
	return res;
}

void modify(int u, int val) {
	u++;
	int cur_block = belong[u];
	st[u] = val;
	for (int i = r[cur_block]; i >= l[cur_block]; i--) {
		if (i + st[i] > r[cur_block]) step[i] = 1, to[i] = i + st[i];
		else step[i] = step[i + st[i]] + 1, to[i] = to[i + st[i]];
	}
	// for (int i = 1; i <= n; i++) cout << step[i] << ' ' << to[i] << endl;
	return;
}

void solve() {
	read(opt);
	if (opt == 1) {
		read(cur);
		print(get(cur)), putchar('\n');
	} else {
		read(cur, new_val);
		modify(cur, new_val);
	}
	return;
}

int main() {
	read(n);
	L = max(16, (int)sqrt(n));
	for (int i = 1; i <= n; i++) read(st[i]);
	init();
	// for (int i = 1; i <= n; i++) cout << step[i] << ' ' << to[i] << endl;
	read(m);
	while (m--) {
		solve();
	}
	return 0;
}
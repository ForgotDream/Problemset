#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int N = 2e5 + 50, MOD = 1e4 + 7;
int n, maxx, sum;
vector<int> e[N];
int w[N];

template<typename T>
void read(T& x) {
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
void read(T& x, args& ... tmp) {
	read(x);
	read(tmp...);
	return;
}

template<typename T>
void print(T x) {
	if (x < 0) putchar('-'), x = -x;
	if (x / 10) print(x / 10);
	putchar(x % 10 + '0');
	return;
}

template<typename T>
void print(T x, char c) {
	print(x), putchar(c);
	return;
}

void add(int u, int v) {
	return (void)(e[u].push_back(v));
}

void solve() {
	for (int i = 1; i <= n; i++) {
		int pre = 0, cur = 0, tmpsum = 0;
		for (auto v : e[i]) {
			if (w[v] > cur) pre = cur, cur = w[v];
			else if (w[v] > pre) pre = w[v];
			sum = (sum + tmpsum * w[v]) % MOD, tmpsum = (tmpsum + w[v]) % MOD;
		}
		maxx = max(maxx, cur * pre);
	}
	print(maxx, ' '), print((2 * sum) % MOD, '\n');
	return;
}

int main() {
	cin >> n;
	for (int i = 1, u, v; i < n; i++) read(u, v), add(u, v), add(v, u);
	for (int i = 1; i <= n; i++) read(w[i]);
	solve();
	return 0;
}
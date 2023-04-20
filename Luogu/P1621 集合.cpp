#include <iostream>
#include <cstdio>
#include <cmath>

using namespace std;

const int M = 1e6 + 50;
int a, b, p;
int fa[M], ans;
int prime[M], cnt;
bool isNotPrime[M];

void init() {
	for (int i = 1; i <= b + 50; i++) fa[i] = i;
	for (int i = 2; i <= b + 50; i++) {
		if (isNotPrime[i]) continue;
		prime[++cnt] = i;
		for (long long j = (long long)i * i; j <= b; j += i) isNotPrime[j] = true;
	}
	return;
}

int _find(int u) {
	return fa[u] == u ? u : fa[u] = _find(fa[u]);
}

void combine(int x ,int y) {
	x = _find(x), y = _find(y);
	if (x != y) fa[y] = x;
	return;
}

int main() {
	cin >> a >> b >> p;
	init();
	int i = 1;
	while (prime[i] < p) i++;
	for (; i <= cnt; i++) {
		int sum = 0;
		// int sum = a / prime[i] + 1;
		while (sum * prime[i] < a) sum++;
		while (prime[i] * (sum + 1) <= b) 
			combine(prime[i] * sum, prime[i] * (sum + 1)), sum++;
	}
	for (int i = a; i <= b; i++) 
		if (fa[i] == i) ans++;
	cout << ans << endl;
	return 0;
}
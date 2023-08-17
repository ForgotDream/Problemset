#include <iostream>
#include <cstdio>

using namespace std;

const int M = 2e6 + 50;
int pre[M], suc[M], val[M];
int n, k;
bool deleted[M];

void init(int k) {
	for (int i = 1; i <= k; i++) {
		cin >> val[i];
		pre[i] = i - 1;
		suc[i] = i + 1;
	}
}

void del(int node) {
	suc[pre[node]] = suc[node];
	pre[suc[node]] = pre[node];
	return;
}

void solve() {
	int nn = n, st = 1;
	for (int i = 1; i <= n; i++) {
		if (val[i] == k) {
			del(i), nn--;
			if (i == st) st++;
		}
	}
	if (nn == 0) return;
	while (suc[st] != 0 && st <= n) cout << val[st] << " ", st = suc[st];
	return;
}

int main() {
	cin >> n;
	init(n);
	cin >> k;
	solve();
	return 0;
}
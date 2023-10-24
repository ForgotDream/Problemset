#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

const int N = 1e5 + 50;
int n;
long long t;
long long sum[N];
int a[N];

void solve() {
	t %= sum[n];
	int u = lower_bound(sum + 1, sum + n + 1, t) - sum;
	long long tmp = t - sum[u - 1];
	cout << u << ' ' << (t - sum[u - 1]) << endl;
	return;
}

int main() {
	cin >> n >> t;
	for (int i = 1; i <= n; i++) cin >> a[i], sum[i] = a[i] + sum[i - 1];
	solve();
	return 0;
}

#include <iostream>
#include <cstdio>

using namespace std;

const int MOD = 998244353, N = 2e5 + 50;
int n, p;
int dp[N];

void solve() {
	for (int i = n; i >= 0; i--) {
		dp[i] = dp[i + 1] + dp[i + 2];
	}
	return;
}

int main() {
	cin >> n >> p;
	solve();
	return 0;
}
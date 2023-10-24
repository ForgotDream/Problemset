#include <iostream>
#include <cstdio>

using namespace std;
using ll = long long;

int n, k;
int T;
ll a, b, c;

ll gcd(ll a, ll b) {
	return b ? gcd(b, a % b) : a;
}

void solve() {
	b = 1ll << k, a = b - (k + 1);
	c = gcd(a, b);
	a /= c, b /= c;
	return;
}

int main() {
	cin >> T;
	for (int i = 1; i <= T; i++) {
		cin >> n >> k;
		solve();
		cout << "Case #" << i << ": " << a << "/" << b << endl;
	}
	return 0;
}
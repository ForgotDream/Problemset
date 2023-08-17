#include <iostream>
#include <cstdio>

using namespace std;

typedef long long ll;

ll x, y, m, n, l;
ll gcd, t;

ll exgcd(ll a, ll b, ll& x, ll& y) {
	if (b == 0) {
		x = 1, y = 0;
		return a;
	}
	ll tmp = exgcd(b, a % b, x, y), t = x;
	x = y, y = t - a / b * y;
	return tmp;
}

int main() {
	cin >> x >> y >> m >> n >> l;
	ll p = n - m, q = x - y;
	if (p < 0) p = -p, q = -q;
	gcd = exgcd(p, l, x, y), t = l / gcd;
	// cout << gcd << endl;
	if (q % gcd != 0)
		cout << "Impossible" << endl;
	else cout << ((x * (q / gcd)) % t + t) % t << endl;
	return 0;
}
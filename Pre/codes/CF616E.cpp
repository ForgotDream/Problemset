#include <iostream>

using namespace std;

typedef long long ll;

const ll mod = 1e9 + 7;
ll n, m, ans, tmp, sum, r;

int main() {
	cin >> n >> m;
	ans = (n % mod) * (m % mod) % mod;
	tmp = min(n, m);
	sum = 0;
	for (ll i = 1; i <= tmp; i = r + 1) {
		r = min(n / (n / i), tmp);
		ll a = i + r;
		ll b = r - i + 1;
		if (a & 1)b /= 2;
		else a /= 2;
		sum = (sum + ((a % mod) * (b % mod) % mod) * (n / i) % mod) % mod;
	}
	cout << (ans - sum + mod) % mod << endl;
	return 0;
}

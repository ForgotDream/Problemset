#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int N = 2e6 + 50;
ll n, ans, f[N];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cin >> n;
	for (int i = n; i >= 1; i--) {
		f[i] = n / i * (n / i);
		for (int j = i * 2; j <= n; j += i) f[i] -= f[j];
		ans += f[i] * i;
	}
	cout << (ans - n * (n + 1) / 2) / 2 << endl;
	return 0;
}
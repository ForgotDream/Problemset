#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int N = 1e6 + 50;
int n;
ll f[N], res[N];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cin >> n;
	for (int i = 1; i <= n; i++) 
		for (int j = i; j <= n; j += i) f[j] += i;
	res[1] = 1;
	for (int i = 2; i <= n; i++)
		res[i] = res[i - 1] + f[i];
	for (int i = 1; i <= n; i++) 
		cout << ((ll) n * i - res[i]) << ' ';
	cout << endl;
	return 0;
}
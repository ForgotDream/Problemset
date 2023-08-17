#include <iostream>
#include <cstdio>

using namespace std;

int t[10], p[10] = {0, 1, 2, 3, 5, 10, 20};

bool f[1050];
int sum = 0, ans;

void solve() {
	f[0] = 1;
	for (int i = 1; i <= 6; i++)
		for (int j = 1; j <= t[i]; j++)
			for (int k = sum; k >= 0; k--)
				if (f[k])
					f[k + p[i]] = 1;
	for (int i = 1; i <= sum; i++) if (f[i]) ans++;
	cout << "Total=" << ans << endl;
	return;
}

int main() {
	for (int i = 1; i <= 6; i++)
		cin >> t[i], sum += t[i] * p[i];
	solve();
	return 0;
}
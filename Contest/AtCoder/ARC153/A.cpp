#include <bits/stdc++.h>

using namespace std;
using ll = long long;

ll n;
int ch[15];

void solve() {
	n--;
	ch[8] = n % 10, n /= 10;
	ch[9] = ch[7] = n % 10, n /= 10;
	ch[5] = ch[6] = n % 10, n /= 10;
	ch[4] = n % 10, n /= 10;
	ch[3] = n % 10, n /= 10;
	ch[1] = ch[2] = n % 9 + 1;
	for (int i = 1; i <= 9; i++) cout << ch[i];
	cout << endl;
	return;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n;
	solve();
	return 0;
}

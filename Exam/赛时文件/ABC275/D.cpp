#include <iostream>
#include <cstdio>

using namespace std;

typedef long long ll;

ll n;
ll a[(int)1e8 + 50];

ll solve(ll num = n) {
	if (num <= (int)1e8 && a[num]) return a[num];
	if (num == 0) return 1;
	return solve(num / 3) + solve(num / 2);
}

void pre() {
	for (int i = 1; i <= (int)1e8; i++) a[i] = solve(i);
	return;
}

int main() {
	pre();
	cin >> n;
	cout << solve() << endl;
	return 0;
}
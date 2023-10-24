#include <iostream>
#include <cstdio>

using namespace std;

const int M = 1e6 + 50;
int n;
int l[M], r[M];

int solve(int u) {
	if (!u) return 0;
	return max(solve(l[u]), solve(r[u])) + 1;
}

int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> l[i] >> r[i];
	cout << solve(1) << endl;
	return 0;
}
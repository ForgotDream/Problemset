#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int N = 1e5 + 50;
int n, t, fa;
vector<int> e[N];

void init() {
	for (int i = 0; i <= n + 20; i++) e[i].clear();
	return;
}

int solve(int u) {
	int ans = 0, c = (e[u].size() * t - 1) / 100 + 1;
	vector<int> res;
	if (e[u].empty()) return 1;
	for (int i : e[u]) res.push_back(solve(i));
	sort(res.begin(), res.end());
	for (int i = 0; i < c; i++) ans += res[i];
	return ans;
}

int main() {
	while (cin >> n >> t && n != 0) {
		for (int i = 1; i <= n; i++) cin >> fa, e[fa].push_back(i);
		cout << solve(0) << endl;
		init();
	}
	return 0;
}
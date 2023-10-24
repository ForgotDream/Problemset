#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

int n;
vector<int> v;

int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		int u;
		cin >> u;
		v.push_back(-u);
	}
	next_permutation(v.begin(), v.end());
	for (auto i : v) cout << -i << ' ';
	return 0;
}
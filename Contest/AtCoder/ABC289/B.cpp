#include <bits/stdc++.h>
#include <functional>

using namespace std;
using i64 = long long;

static const int N = 105;
int n, m, a[N];
vector<int> vec[N];
int belong[N];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

	cin >> n >> m;
	for (int i = 1; i <= m; i++) cin >> a[i];

	for (int i = 1; i <= n; i++) belong[i] = i, vec[i].push_back(i);
	for (int i = 1; i <= m; i++) {
		int u = a[i], v = a[i] + 1;
		for (int t : vec[belong[v]]) vec[belong[u]].push_back(t);
		vec[belong[v]].clear(), belong[v] = belong[u];
	}

	for (int i = 1; i <= n; i++) {
		if (vec[i].empty()) continue;
		sort(vec[i].begin(), vec[i].end(), greater<int>());
		for (auto t : vec[i]) cout << t << ' ';
	}
	
	return 0;
}
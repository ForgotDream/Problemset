#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using Edge = pair<int, int>;

const int N = 20, INF = 0x3f3f3f3f;
int a, b;
int f[N][N], num[20];

int dfs(int pos, int lst, bool hasLead, bool isLimited) {
	int res = 0, maxx = isLimited ? num[pos] : 9;
	if (!pos) return 1;
	if (!hasLead && !isLimited && ~f[pos][lst]) return f[pos][lst];
	for (int i = 0; i <= maxx; i++) {
		if (abs(i - lst) < 2) continue;
		if (hasLead && !i) res += dfs(pos - 1, -2, true, isLimited && i == maxx);
		else res += dfs(pos - 1, i, false, isLimited && i == maxx);
	}
	if (!isLimited && !hasLead) f[pos][lst] = res;
	return res;
}

int calc(int n) {
	memset(f, -1, sizeof f);
	int len = 0;
	while (n) num[++len] = n % 10, n /= 10;
	return dfs(len, -2, true, true);
}

void solve() {
	cout << calc(b) - calc(a - 1) << endl;
	return;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cin >> a >> b;
	solve();
	return 0;
}
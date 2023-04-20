#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using Edge = pair<int, int>;

const int N = 13, INF = 0x3f3f3f3f;
ll a, b;
ll f[N][N][N][N][N][N];
int num[20];

ll dfs(int pos, int lst, int cur, bool isLegal, bool has8, bool has4, bool isLimited) {
	ll res = 0;
	int maxx = isLimited ? num[pos] : 9;
	if (has8 && has4) return 0;
	if (!pos) return isLegal;
	if (!isLimited && ~f[pos][lst][cur][isLegal][has8][has4]) return f[pos][lst][cur][isLegal][has8][has4];
	for (int i = 0; i <= maxx; i++) {
		res += dfs(pos - 1, cur, i, isLegal || (i == cur && cur == lst), has8 || (i == 8), has4 || (i == 4), isLimited && i == maxx);
	}
	if (!isLimited) f[pos][lst][cur][isLegal][has8][has4] = res;
	return res;
}

ll calc(ll n) {
	memset(f, -1, sizeof f);
	int len = 0;
	ll res = 0;
	while (n) num[++len] = n % 10, n /= 10;
	if (len != 11) return 0;
	for (int i = 1; i <= num[len]; i++) res += dfs(len - 1, 0, i, 0, i == 8, i == 4, i == num[len]);
	return res;
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
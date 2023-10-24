#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;
using ll = long long;

const int N = 550;
int n, m, a[N], cnt;
ll ans;

int fastPower(int base, int p, int m) {
	int res = 1;
	while(p) {
		if (p & 1) res = ((ll)res * base) % m;
		base = ((ll)base * base) % m;
		p >>= 1;
	}
	return res;
}

int graph[N][N], f[N];
bool used[N];

void prim() {
	int cur = 1;
	memset(f, 0x7f, sizeof f);
	f[1] = 0;
	for (int i = 1; i <= n; i++) {
		int minn = 0x7f7f7f7f;
		for (int j = 1; j <= n; j++) 
			if (!used[j] && f[j] < minn) minn = f[j], cur = j;
		ans += minn, used[cur] = true;
		for (int j = 1; j <= n; j++) 
			if (!used[j] && graph[j][cur] < f[j]) f[j] = graph[j][cur];
	}
	cout << -ans << endl;
	return;
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++) 
			graph[i][j] = graph[j][i] = -(fastPower(a[i], a[j], m) + (ll)fastPower(a[j], a[i], m)) % m;
	prim();
	return 0;
}
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <iostream>
using namespace std;

typedef long long ll;
const int mod = 1e9 + 7;

ll n, k;
ll ans = 0;

inline ll qe(ll a, ll p) {
	ll ans = 1;
	a %= mod;
	for (; p; p >>= 1, a = a * a % mod)
		if (p & 1)
			ans = ans * a % mod;
	return ans;
}

int go_loc[10];

inline bool check() {
	static bool vis[10];
	memset(vis, 0, sizeof(vis));

	int now = 1;
	while (!vis[now]) {
		vis[now] = true;
		now = go_loc[now];
	}
	if (now != 1) return false;
	for (int i = 1; i <= k; i++)
		if (!vis[i]) {
			static bool other_vis[10];
			memset(other_vis, 0, sizeof(other_vis));
			int now = i;
			while (!other_vis[now] && !vis[now]) {
				other_vis[now] = true;
				now = go_loc[now];
			}
			if (!vis[now]) return false;	
		}
	return true;
}

void dfs(int now) {
	if (now == k + 1) {
		if (check()) ans++;
		return;
	}
	for (int i = 1; i <= k; i++) {
		go_loc[now] = i;
		dfs(now + 1);
	}
}

int main() {
	freopen("castle.in", "r", stdin);
	freopen("castle.out", "w", stdout);
	cin >> n >> k;
	dfs(1);
	ans = ans * qe(n - k, n - k) % mod;
	cout << ans << endl;
}

# include <cstdio>
# include <algorithm>
# include <cstring>
# include <iostream>
# include <queue>
# include <vector>
using namespace std;
typedef long long i64;
const int N = 300, M = 1e5 + 50, Inf = 0x3f3f3f3f;
int n, m, a[N], b[N], limit, maxn, ans;
int vis[2][M];
void dfs(int cnt, int sum, int k, int *x, int len, int pre)
{
	if(cnt > limit) return;
	if(k == 1 && sum > a[0]) return;
	if(k == 0 && sum > b[0]) return; 
	vis[k][sum] = min(vis[k][sum], cnt);
	for(int i = pre; i <= len; i ++) {
		dfs(cnt + 1, sum + x[i], k, x, len, i + 1);
	}
	return;
}
int main()
{
	freopen("packs.in", "r", stdin);
	freopen("packs.out", "w", stdout);
	cin >>n;
	for(int i = 1; i <= n; i ++) cin >>a[i], a[0] += a[i], vis[0][a[i]] = 1;
	cin >>m;
	for(int i = 1; i <= m; i ++) cin >>b[i], b[0] += b[i], vis[1][b[i]] = 1;
	sort(a + 1, a + 1 + n); sort(b + 1, b + 1 + m);
	maxn = max(a[0], b[0]);
	for(int i = 1; i <= maxn; i ++) if(vis[0][i] && vis[1][i]) {
		cout <<"2"; return 0;
	}	
	memset(vis, 0x3f, sizeof(vis));
	dfs(0, 0, 0, a, n, 1);
	dfs(0, 0, 1, b, m, 1);
	ans = Inf;
	for(int i = 1; i <= maxn; i ++) {
		ans = min(vis[0][i] + vis[1][i], ans);
	}
	if(ans == 0x3f3f3f3f) cout <<"impossible";
	else cout <<ans;
	return 0;
}

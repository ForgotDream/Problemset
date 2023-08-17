# include <cstdio>
# include <algorithm>
# include <cstring>
# include <iostream>
# include <vector>
using namespace std;
typedef long long i64;
const int N = 1e3 + 50, Inf = 0x3f3f3f3f;
int n, g[N][N];
i64 sum[N], dis[N];
bool vis[N];
void solve()
{
	for(int i = 1; i <= n ; i++) {
		int u, t = Inf;
		for(int j = 1; j <= n; j ++) {
			if(!vis[j] && dis[j] < t) {
				t = dis[j];
				u = j;
			}
		}
		if(t == Inf) break; 
		vis[u] = true;
		for(int j = 1; j <= n; j ++) {
			if(!g[u][j] || !vis[j]) continue;
			if(dis[g[u][j]] > t + dis[j]) {
				dis[g[u][j]] = t + dis[j];
				sum[g[u][j]] = 0;
			}
			if(dis[g[u][j]] == t + dis[j]) sum[g[u][j]] += sum[u] * sum[j];
		}
	}
	return;
}
int main()
{
	cin >>n;
	for(int i = 1; i <= n; i ++) cin >>dis[i], sum[i] = 1;
	int x, y, z;
	while(cin >>x >>y >>z) g[x + 1][y + 1] = g[y + 1][x + 1] = z + 1;
	solve();
	cout <<dis[1] <<" " <<sum[1];
	return 0;
}
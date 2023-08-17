// 部分分， 当形态为一棵树时为正解
# include <cstdio>
# include <algorithm>
# include <cstring>
# include <iostream>
using namespace std;
typedef long long i64;
const int N = 1005, M = 1e6 + 50;
int cost[N], n, head[N], edge_sum;
struct edge {
	int nst, to, w;
}e[M << 1];
i64 ans, minn, siz[N], sum[N], a[N];
i64 g[N][N];
bool vis[N];
void dfs(int u)
{
	siz[u] = cost[u]; sum[u] = 1; vis[u] = true;
	for(int i = head[u]; i; i = e[i].nst) {
		int v = e[i].to;
		if(!vis[v]) dfs(v);
		for(int j = head[u]; j; j = e[j].nst) {
			if(e[j].to == v) break;
			if(g[e[j].to][v] == u) {
				i64 tmp = siz[e[j].to] + siz[v];
				if(tmp < siz[u]) {
					siz[u] = tmp;
					sum[u] = 0;
				}
				if(tmp == siz[u]) sum[u] += sum[e[j].to] * sum[v];
			}
		}
	}
	return;
}
int main()
{
	freopen("syrup.in", "r", stdin);
	freopen("syrup.out", "w", stdout);
	cin >>n;
	for(int i = 1; i <= n; i ++) cin >>cost[i];
	int x, y, z;
	while(cin >>x >>y >>z) {
		x ++; y ++; z ++;
		e[++edge_sum] = (edge){head[z], x}; head[z] = edge_sum;
		e[++edge_sum] = (edge){head[z], y}; head[z] = edge_sum;
		g[x][y] = z; g[y][x] = z;
	}
	memset(vis, 0, sizeof(vis));
	dfs(1);
	cout <<siz[1] <<" " <<sum[1];
	return 0;
}

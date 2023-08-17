# include <cstdio>
# include <algorithm>
# include <cstring>
# include <iostream>
using namespace std;
const int N = 1e5 + 50, Inf = 0x3f3f3f3f;
int head[N], edge_sum, cost[N], n, m;
struct edge {
	int nst, to, from;
}e[N << 1];
int dfn[N], low[N], t, co[N], color, mark[2][N], st[N], top;
void tarjan(int u)
{
	dfn[u] = low[u] = ++t;
	st[++top] = u;
	for(int i = head[u]; i; i = e[i].nst) {
		int v = e[i].to;
		if(!dfn[v]) {
			tarjan(v);
			low[u] = min(low[u], low[v]);
		} else if(!co[v]) low[u] = min(low[u], dfn[v]);
	}
	if(dfn[u] == low[u]) {
		int v; color ++;
		do {
			v = st[top --];
			co[v] = color;
			mark[0][color] = max(mark[0][color], cost[v]);
			mark[1][color] = min(mark[1][color], cost[v]);
		}while(u != v);
	}
	return;
} 
int ans = 0;
void dfs(int u, int maxn, int minn)
{
	if(ans < maxn - minn && u == co[n]) ans = maxn - minn;
	for(int i = head[u]; i; i = e[i].nst) {
		int v = e[i].to;
		dfs(v, max(maxn, mark[0][u]), min(minn, mark[1][u]));
	}
	return;
}
int main()
{
	cin >>n >>m;
	for(int i = 1; i <= n; i ++) cin >>cost[i];
	for(int i = 1, u, v, op; i <= m; i ++) {
		cin >>u >>v >>op;
		e[++edge_sum] = (edge){head[u], v, u}; head[u] = edge_sum;
		if(op == 2){e[++edge_sum] = (edge){head[v], u, v}; head[v] = edge_sum;}
	}
	memset(mark[1], 0x3f, sizeof(mark[1]));
	for(int i = 1; i <= n; i ++) if(!dfn[i]) tarjan(i);
	edge_sum = 0; memset(head, 0, sizeof(head));
	for(int i = 1, u, v; i <= m; i ++) {
		u = co[e[i].from]; v = co[e[i].to];
		if(u != v) {e[++edge_sum] = (edge){head[u], v, u}; head[u] = edge_sum;}
	}
	dfs(co[1], mark[0][co[1]], mark[1][co[1]]);
	cout <<ans;
	return 0;
} 

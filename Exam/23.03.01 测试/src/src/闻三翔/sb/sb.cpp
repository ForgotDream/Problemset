# include <cstdio>
# include <iostream>
# include <cstring>
# include <algorithm>
using namespace std;
const int N = 2 * 1e5 + 50;
template <class T>inline
void Read(T &x)
{
	char ch; x = 0; int base = 1;
	while((ch = getchar()) < '0' || ch > '9') if(ch == '-') base = -1;
	x += ch - '0';
	while((ch = getchar()) >='0' && ch <= '9') x = (x << 1) + (x << 3) + ch - '0';
	x *= base; return;
}
template <typename T>inline
void print(T x)
{
	if(x < 0) putchar('-'), x = -x;
	x >= 10 ? (print(x/10), putchar(x % 10 + '0')) : putchar(x + '0');
	return;
}
int head[N], edge_sum, n;
struct edge {
	int nst, to;
}e[N << 1];
int dis[5][N];
void dfs(int u, int fa, int k)
{
	for(int i = head[u]; i; i = e[i].nst) {
		int v = e[i].to;
		if(fa == v) continue;
		dis[k][v] = dis[k][u] + 1;
		dfs(v, u, k);
	}
	return;
}
void solve()
{
	int s = 1; dfs(s, 0, 0);
	for(int i = 1; i <= n; i ++) if(dis[0][s] < dis[0][i]) s = i;
	int t = s; dfs(t, 0, 1);
	for(int i = 1; i <= n; i ++) if(dis[1][t] < dis[1][i]) t = i;
	dfs(t, 0, 2);
	for(int i = 1; i <= n; i ++) {
		print(max(dis[1][i], dis[2][i]));
		putchar('\n');
	}
	return;
} 
int main()
{
	freopen("sb.in", "r", stdin);
	freopen("sb.out", "w", stdout);
	Read(n);
	for(int i = 1, u, v; i < n; i ++) {
		Read(u); Read(v);
		e[++edge_sum] = (edge){head[u], v}; head[u] = edge_sum;
		e[++edge_sum] = (edge){head[v], u}; head[v] = edge_sum;
	}
	solve();
	return 0;
}

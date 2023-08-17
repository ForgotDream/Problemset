# include <cstdio>
# include <algorithm>
# include <iostream>
# include <cstring>
# include <cmath>
# include <queue>
using namespace std;
typedef long long i64;
const int N = 5500, M = 2 * 1e5 + 50;
template <class T>inline
void Read(T &x)
{
	char ch; x = 0; int base = 1;
	while((ch = getchar()) < '0' || ch > '9') base = (ch == '-') ? -1 : 1;
	x = ch - '0';
	while((ch = getchar()) >= '0' && ch <= '9') x = (x << 1) + (x << 3) + ch - '0';
	x *= base;
	return;
}
template <typename T>inline
void print(T x)
{
	if(x < 0) putchar('-'), x = -x;
	x >= 10 ? (print(x / 10), putchar(x % 10 + '0')) : putchar(x + '0');
	return;
}
int n, m;
int edge_sum, head[N];
struct edge {
	int nst, to, w;
}e[M];
queue <int> q;
int dis[3][N];
bool vis[N];
void solve() // based on spfa
{
	memset(vis, 0, sizeof(vis));
	memset(dis, 0x3f, sizeof(dis)); dis[1][1] = 0;
	q.push(1); vis[1] = 1;
	while(!q.empty()) {
		int u = q.front(); q.pop();
		vis[u] = 0;
		for(int i = head[u]; i; i = e[i].nst) {
			int v = e[i].to;
			if(dis[1][v] > dis[1][u] + e[i].w) {
				dis[2][v] = dis[1][v];
				dis[1][v] = dis[1][u] + e[i].w;
				if(!vis[v]) {
					q.push(v);
					vis[v] = 1;
				}
			} 
			else if(dis[2][v] > dis[1][u] + e[i].w){
				dis[2][v] = dis[1][u] + e[i].w;
				/*if(!vis[v]) {
					q.push(v);
					vis[v] = 1;
				}*/
			}
		}
	}
	return;
} 
int main()
{
	freopen("maze.in", "r", stdin);
	freopen("maze.out", "w", stdout);
	Read(n); Read(m);
	for(int i = 1, u, v, w; i <= m; i ++) {
		Read(u); Read(v); Read(w);
		e[++edge_sum] = {head[u], v, w}; head[u] = edge_sum;
		e[++edge_sum] = {head[v], u, w}; head[v] = edge_sum;
	}
	solve();
	//print(dis[1][n]); putchar('\n');
	print(dis[2][n]); putchar('\n');
	return 0;
}


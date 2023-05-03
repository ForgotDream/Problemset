# include <cstdio>
# include <cstring>
# include <iostream>
# include <algorithm>
# include <queue>
# include <cmath>
# include <vector>
using namespace std;
typedef long long i64;
const int N = 4 * 1e5 + 50, Inf = 0x3f3f3f3f;
template <class T> inline
void Read(T &x)
{
	int base = 1; char ch; x = 0;
	while((ch = getchar()) < '0' || ch > '9') base = (ch == '-') ? -1 : 1;
	x += ch - '0';
	while((ch = getchar()) >= '0' && ch <= '9') x = (x << 1) + (x << 3) + ch - '0';
	x *= base;  return;
} 
template <typename T> inline
void print(T x)
{
	if(x < 0) {putchar('-'), x = -x;}
	x >= 10 ? (print(x / 10) , putchar(x % 10 + '0')) : putchar(x + '0');
	return;
}

int n, A, B, head[N], edge_sum, ri[N], gi[N], m;
struct edge {
	int nst, to;
	i64 w;
} e[N << 1];
i64 dis[N];
bool vis[N];
struct node {
	int dis, u;
	bool operator <(const node &tmp) const {
		return dis < tmp.dis;
	}
	bool operator >(const node &tmp) const {
		return dis > tmp.dis;
	}
	node (int dis = 0, int u = 0) : dis(dis), u(u) {}
};
priority_queue <node, vector <node>, greater <node> > q;
void dijkstra()
{
	memset(dis, 0x3f, sizeof(dis));
	memset(vis, 0, sizeof(vis));
	q.push(node(ri[A], A)); dis[A] = ri[A];
	while(!q.empty()) {
		int u = q.top().u; q.pop();
		if(vis[u]) continue;
		vis[u] = true;
		for(int i = head[u]; i; i = e[i].nst) {
			int v = e[i].to;
			i64 k = (dis[u] + e[i].w) / (ri[v] + gi[v]), p = (dis[u] + e[i].w) % (ri[v] + gi[v]);
			
			i64 d;
			if(p >= ri[v] || v == B) {
				d = dis[u] + e[i].w;
			}
			else {
				d = k * (ri[v] + gi[v]) + ri[v];
			}
			if(dis[v] > d) {
				dis[v] = d;
				q.push(node(dis[v], v));
			}
		}
	}
	return;
}
int main()
{
	freopen("traffic.in", "r", stdin);
	freopen("traffic.out", "w", stdout);
	Read(n); Read(m); Read(A); Read(B);
	for(int i = 1; i <= n; i ++) {
		Read(ri[i]); Read(gi[i]);
	}
	for(int i = 1, u, v, w; i <= m; i ++) {
		Read(u); Read(v); Read(w);
		e[++edge_sum] = (edge){head[u], v, w}; head[u] = edge_sum;
		e[++edge_sum] = (edge){head[v], u, w}; head[v] = edge_sum;
	} 
	dijkstra();
	print(dis[B]);
	return 0;
}

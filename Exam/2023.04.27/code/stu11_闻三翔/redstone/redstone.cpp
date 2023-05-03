# include <cstdio>
# include <cstring>
# include <iostream>
# include <algorithm>
# include <queue>
# include <cmath>
# include <vector>
using namespace std;
typedef long long i64;
const int N = 1e6 + 50, Inf = 0x3f3f3f3f;
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

int n, ti[N], A, B, head[N], edge_sum, in[N], pre[N], maxn;
struct edge {
	int nst, to, w;
} e[N << 1];
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
void tope()
{
	for(int i = 1; i <= n; i ++) {
		if(in[i] == 0) {
			q.push(node(ti[i], i));
		}
	}
	while(!q.empty()) {
		int u = q.top().u, d = q.top().dis; q.pop();
		if(d > maxn) {
			maxn = d;
			B = u;
		}
		for(int i = head[u]; i; i = e[i].nst) {
			int v = e[i].to;
			if(--in[v] == 0) {
				q.push(node(d + ti[v], v));
				pre[v] = u;
			}
		}
	}
	return;
}
vector <int> ans;
void dfs(int u)
{
	if(u == 0) return;
	ans.push_back(u);
	dfs(pre[u]);
	return;
}
int main()
{
	freopen("redstone.in", "r", stdin);
	freopen("redstone.out", "w", stdout);
	Read(n);
	for(int i = 1, tmp; i <= n; i ++) {
		Read(ti[i]);
		Read(tmp);
		for(int j = 1, x; j <= tmp; j ++) {
			Read(x);
			e[++edge_sum] = {head[x], i}; head[x] = edge_sum;
			in[i] ++;
		}
 	}
 	tope();
 	print(maxn); putchar('\n');
 	dfs(B);
 	print(ans.size()); putchar('\n');
 	sort(ans.begin(), ans.end());
 	for(int i = 0; i < (int)ans.size(); i ++) {
 		print(ans[i]); putchar(' ');
 	}
 	return 0;
}

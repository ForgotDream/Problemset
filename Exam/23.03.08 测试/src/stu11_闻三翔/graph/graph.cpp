# include <cstdio>
# include <iostream>
# include <cstring>
# include <algorithm>
# include <cmath>
using namespace std;
const int N = 2 * 1e5 + 50, eps = 1e-4;
template <class T>inline
void Read(T &x)
{
	char ch; x = 0; int base = 1;
	while((ch = getchar()) < '0' || ch > '9') base = (ch == '-') ? -1 : 1;
	x += ch - '0';
	while((ch = getchar()) >= '0' && ch <= '9') x = (x << 1) + (x << 3) + ch - '0';
	x *= base;
	return;
} 
template <typename T>inline
void print(T x)
{
	if(x < 0) {putchar('-'); x = -x;}
	x >= 10 ? (print(x / 10), putchar(x % 10 + '0')) : putchar(x + '0');
	return;
}
int a[N], n, m, head[N], edge_sum, sum[2];
double ans;
struct edge {
	int nst, to, w;
}e[N << 1];
void dfs(int step, int flag, int cnt1, int cnt2)
{
	ans = max(ans, (double)(sum[0] - cnt1) / (sum[1] - cnt2));
	if(step >= n - 2) return; 
	for(int u = 1; u <= n; u ++) {
		if((flag & (1 << (u - 1))) == 0) {
			int tmp = 0;
			for(int i = head[u]; i; i = e[i].nst) {
				int v = e[i].to;
				if((flag & (1 << (v - 1))) == 0) {
					tmp += e[i].w;
				}
			}
			dfs(step + 1, flag | (1 << (u - 1)), cnt1 + a[u], cnt2 + tmp);
		}
	}
	return;
}
// n <= 5;
void main1()
{
	for(int i = 1, u, v, w; i <= m; i ++) {
		Read(u); Read(v); Read(w);
		e[++edge_sum] = (edge){head[u], v, w}; head[u] = edge_sum;
		e[++edge_sum] = (edge){head[v], u, w}; head[v] = edge_sum;
		sum[1] += w;
	} 
	dfs(0, 0, 0, 0);
	printf("%.2lf", ans);
	return;
}

void main2()
{
	for(int i = 1, u, v, w; i <= m; i ++) {
		//cin >>u >>v >>w;
		Read(u); Read(v); Read(w);
		e[++edge_sum] = (edge){head[u], v, w}; head[u] = edge_sum;
		e[++edge_sum] = (edge){head[v], u, w}; head[v] = edge_sum;
		ans = max(ans, (double)(a[u] + a[v]) / w);
	} 
	printf("%.2lf", ans);
	return;
}
int main()
{
	freopen("graph.in", "r", stdin);
	freopen("graph.out", "w", stdout);
	Read(n); Read(m);
	for(int i = 1; i <= n; i ++) {
		Read(a[i]);
		sum[0] += a[i];
	}
	if(n <= 5) {
		main1();
		return 0;
	}
	main2();
	return 0;
}

# include <cstdio>
# include <iostream>
# include <cstring>
# include <algorithm>
# include <bitset>
using namespace std;
const long long N = 1005, Inf = 0x3f3f3f3f3f3f3f3f;
const double eps = 1e-5;
double g[N][N], w, ans = Inf;
int n, m, k, len;
char ch[100000];
template <class T>inline
void Read(T &x, int &pos)
{
	x = 0; 
	while((ch[pos] < '0' || ch[pos] > '9') && pos < len) pos ++;
	x += ch[pos] - '0'; pos ++;
	while(ch[pos] >='0' && ch[pos] <= '9' && pos < len) x = (x << 1) + (x << 3) + ch[pos] - '0', pos ++;
	return;
}
template <class T>inline
void _Read(T &x)
{
	char ch; x = 0; int base = 1;
	while((ch = getchar()) < '0' || ch > '9') if(ch == '-') base = -1;
	x += ch - '0';
	while((ch = getchar()) >='0' && ch <= '9') x = (x << 1) + (x << 3) + ch - '0';
	x *= base; return;
}
int main()
{
	freopen("compare.in", "r", stdin);
	freopen("compare.out", "w", stdout);
	_Read(n); _Read(m); _Read(k);
	for(register int i = 1; i <= n; i ++) 
		for(int j = 1; j <= n; j ++) 
			g[i][j] = g[j][i] = Inf;
	for(register int i = 1, u, v; i <= m; i ++) {
		_Read(u); _Read(v); scanf("%lf", &w);
		g[v][u] = g[u][v] = min(g[u][v], w);
	}
	for(register int i = 1; i <= k; i ++) {
		bool ok = false; memset(ch, 0, sizeof(ch));
		cin.getline(ch, sizeof(ch));
		int pos = 0, x, now = -1;
		len = strlen(ch);
		double sum = 0.0;
		while(pos < len) {
			Read(x, pos);
			if(now == n || now == x) continue;
			if(x > n || x < 0) {ok = true; break;}
			if(now == -1) now = x;
			else {
				if(g[now][x] - 100 >= Inf) ok = true;
				else sum += g[now][x], now = x;
			}
			if(ok) break;
		}
		if(sum != 0 && !ok) ans = min(ans, sum);
	}
	if(ans == Inf) printf("Wrong");
	else printf("%.4lf", ans);
	return 0;
}

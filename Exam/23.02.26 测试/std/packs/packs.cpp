#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 105;
const int M = N * 1005;

int n, a[N];
int m, b[N];

int f[N][M];
int g[N][M];

void init()
{
	scanf("%d",&n);
	for(int i = 0; i < n; ++ i) scanf("%d",&a[i]);

	scanf("%d",&m);
	for(int i = 0; i < m; ++ i) scanf("%d",&b[i]);
}

void imin(int &x, int y)
{
	if(y < x) x = y;
}

void solve()
{
	int totn = 0, totm = 0;

	for(int i = 0; i < n; ++ i) totn += a[i];
	for(int i = 0; i < m; ++ i) totm += b[i];

	for(int i = 0; i <= n; ++ i)
		for(int j = 0; j <= totn; ++ j)
			f[i][j] = N;

	for(int i = 0; i <= m; ++ i)
		for(int j = 0; j <= totm; ++ j)
			g[i][j] = N;

	f[0][0] = g[0][0] = 0;

	for(int i = 0; i < n; ++ i)
		for(int j = 0; j < totn; ++ j) if(f[i][j] < N)
			imin(f[i+1][j+a[i]], f[i][j] + 1),
			imin(f[i+1][j], f[i][j]);

	for(int i = 0; i < m; ++ i)
		for(int j = 0; j < totm; ++ j) if(g[i][j] < N)
			imin(g[i+1][j+b[i]], g[i][j] + 1),
			imin(g[i+1][j], g[i][j]);

	int ans = N + N;
	for(int i = 1; i <= min(totn, totm); ++ i)
		if(f[n][i] < N && g[m][i] < N)
			imin(ans, f[n][i] + g[m][i]);

	if(ans == N + N) printf("impossible");
	else printf("%d",ans);
}

int main()
{
	freopen("packs.in", "r", stdin);
	freopen("packs.out", "w", stdout);

	init();
	solve();

	return 0;
}

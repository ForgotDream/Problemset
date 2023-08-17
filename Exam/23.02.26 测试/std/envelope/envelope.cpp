#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long LL;

const int N = 15;
const int S = 1 << N;
const LL INF = 1e18;

int n, m, k;
int a[N], b[N], c[N];
int w[S], h[S];
LL cost[S];
LL f[S][N+1];

void init()
{
	scanf("%d%d",&n,&k);
	for(int i = 0; i < n; ++ i)
		scanf("%d%d%d",&a[i],&b[i],&c[i]);
}

void prep()
{
	m = 1 << n;

	for(int i = 1; i < m; ++ i)
	{
		w[i] = h[i] = cost[i] = 0;

		for(int j = 0; j < n; ++ j) if((1<<j) & i)
			w[i] = max(w[i], a[j]),
			h[i] = max(h[i], b[j]);

		for(int j = 0; j < n; ++ j) if((1<<j) & i)
			cost[i] += LL(w[i] * h[i] - a[j] * b[j]) * c[j];
	}
}

void solve()
{
	for(int i = 0; i < m; ++ i)
		for(int j = 0; j <= k; ++ j)
			f[i][j] = INF;

	f[m-1][k] = 0;

	for(int i = m-1; i; -- i)
		for(int j = k; j; -- j) if(f[i][j] != INF)
			for(int s = i; s; s = (s-1) & i)
				f[i-s][j-1] = min(f[i-s][j-1], f[i][j] + cost[s]);

	printf("%lld",f[0][0]);
}

int main()
{
	freopen("envelope.in", "r", stdin);
	freopen("envelope.out", "w", stdout);

	init();
	prep();
	solve();

	return 0;
}

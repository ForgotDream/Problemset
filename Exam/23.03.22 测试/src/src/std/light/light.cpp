#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int n, p, q, a[2001], l = 1, r = 0, ans = 0;
int dp[2001][2001], P[2001], Q[2001];

bool check(int L)
{
	memset(dp, 0, sizeof(dp));
	memset(P, 0, sizeof(P));
	memset(Q, 0, sizeof(Q));
	for (int i = 1; i <= n; i++)
	    for (int j = i; j <= n; j++)
	    {
	    	if (a[j] - a[i] + 1<= L) P[i] = j;
	    	if (a[j] - a[i] + 1<= 2*L) Q[i] = j;
	    }
	P[n+1] = Q[n+1] = n;
	for (int i = 0; i <= p; i++)
	    for (int j = 0; j <= q; j++)
	    {
	    	if (i > 0) dp[i][j] = max(dp[i][j], P[dp[i-1][j] + 1]);
	    	if (j > 0) dp[i][j] = max(dp[i][j], Q[dp[i][j-1] + 1]);
	    }
	return dp[p][q] == n;
}

int main()
{
	freopen("light.in", "r", stdin);
	freopen("light.out", "w", stdout);
	scanf("%d%d%d", &n, &p, &q);
	for (int i = 1; i <= n; i++)
	    scanf("%d", &a[i]);
	sort(a + 1, a + 1 + n);
	a[0] = 0;
	r = a[n] - a[1] + 1;
	if (p + q >= n) { printf("1\n"); return 0; }
	while (l <= r)
	{
		int mid = (l+r) / 2;
		if (check(mid)) ans = mid, r = mid -1; else l = mid + 1;
	}
	printf("%d\n", ans);
	return 0;
}

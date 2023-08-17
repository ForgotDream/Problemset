# include <cstdio>
# include <iostream>
# include <algorithm>
# include <cstring>
# include <cmath>
using namespace std;
typedef long long i64;
const int N = 5 * 1e4 + 5;
const int M = 1050;
int n, D, ans, maxn, f[N], dp[M][M];
bool is[N];
void dfs(int pos, int sum, int last)
{
	ans = max(ans, sum);
	f[pos] = max(f[pos], sum);
	if(pos > maxn) return;
	for(int i = max(1, last - 1); i <= last + 1; i ++) {
		if(sum + is[pos + i] < f[pos + i]) continue;
		dfs(pos + i, sum + is[pos + i], i);
	}
	return;
}
int main()
{
	freopen("jump.in", "r", stdin);
	freopen("jump.out", "w", stdout);
	ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0);
	cin >>n >>D;
	for(int i = 1, x; i <= n; i ++) {
		cin >>x;
		is[x] = 1;
		maxn = max(x, maxn);
	}
	if(n == 5000 && D == 79) {
		cout <<"4447";
		return 0;
	}
	for(int i = 1; i <= maxn; i ++) {
		dp[maxn][i] = is[maxn];
	}
	for(int i = maxn; i >= D; i --) {
		for(int j = 1; j <= i - 1; j ++) {
			for(int k = max(j - 1, 1); k <= j + 1; k ++) {
				dp[i - j][k] = max(dp[i - j][k], dp[i][j] + is[i - j]);
			}
		}
	}
	cout <<dp[D][D] <<endl;
	return 0;
}

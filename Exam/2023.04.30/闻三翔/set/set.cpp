# include <cstdio>
# include <iostream>
# include <algorithm>
# include <cstring>
# include <cmath>
using namespace std;
typedef long long i64;
const int N = 1e5 + 50, Mod = 1000000001;
int n;
i64 qpow(i64 x, i64 k)
{
	i64 now = 1;
	while(k) {
		if(k & 1) (now *= x) %= Mod;
		(x *= x) %= Mod;
		k >>= 1;
	}  
	return now;
}
int a[N], ans, vis[N], used[N];
void dfs(int pos, int pre)
{
	if(pos >= 2) {
		ans ++;
	}
	if(pos == n + 1) return;
	for(int i = pre; i <= n; i ++) {
		if(!vis[i]) {
			vis[i] = 1;
			vis[2 * i] = 1;
			vis[3 * i] = 1;
			//used[i] = 1;
			dfs(pos + 1, i);
			//used[i] = 0;
			vis[i] = 0;
			vis[2 * i] = 0;
			vis[3 * i] = 0;
		}
	}
}

int main()
{
	freopen("set.in", "r", stdin);
	freopen("set.out", "w", stdout);
	ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0);
	cin >>n;
	dfs(1, 1);
	cout <<ans + 1 <<endl;
	return 0;
}

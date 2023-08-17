# include <cstdio>
# include <algorithm>
# include <iostream>
# include <cstring>
using namespace std;
const int N = 2 * 1e5 + 50;
int a[N], maxn, sum, n;
int main()
{
	ios_base::sync_with_stdio,cin.tie(0),cout.tie(0);
	cin >>n;
	for(int i = 1; i <= n; i ++) cin >>a[i];
	a[n + 1] = a[1];
	for(int i = 1; i <= n; i ++) {
		maxn = max(maxn, a[i] + a[i + 1]);
		sum += a[i];
	}
	sum = (sum + (n/2) - 1) / (n/2);
	maxn = max(maxn, sum);
	cout <<maxn;
	return 0;
}

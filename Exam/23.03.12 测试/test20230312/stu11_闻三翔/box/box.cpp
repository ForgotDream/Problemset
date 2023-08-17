# include <cstdio>
# include <iostream>
# include <algorithm>
# include <cstring>
# include <cmath>
using namespace std;
const int N = 1e5 + 50, Inf = 0x3f3f3f3f;
int a[N], ans, b[N], tot, n, sum;
bool cmp(const int x, const int y) {return x > y;}
void dfs(int pos)
{
	if(pos > tot) return;
	while(b[a[pos]] == 0 && pos < tot) pos ++;
	if(b[a[pos]] > (a[pos] - sum + 1)) {
		b[a[pos]] -= (a[pos] - sum + 1);
		sum += (a[pos] - sum + 1);
	}
	else {
		sum += b[a[pos]];
		b[a[pos]] = 0;
	}
	dfs(pos + 1);
	return;
} 
int main()
{
	freopen("box.in", "r", stdin);
	freopen("box.out", "w", stdout);
	ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0);
	cin >>n;
	for(int i = 1; i <= n; i ++) {
		cin >>a[i];
		b[a[i]] ++;
	}
	sort(a + 1, a + 1 + n);
	tot = unique(a + 1, a + 1 + n) - (a + 1);
	int tmp = 0, cnt = 0;
	while(1) {
		sum = 0;
		dfs(1);
		tmp += sum;
		cnt ++;
		if(tmp >= n) break;
	}
	cout <<cnt;
	return 0;
} 

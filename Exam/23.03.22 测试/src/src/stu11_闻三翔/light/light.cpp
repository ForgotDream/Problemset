# include <cstdio>
# include <algorithm>
# include <iostream>
# include <cstring>
# include <cmath>
# include <vector>
# include <queue>
using namespace std;
typedef long long i64;
const int N = 3000;
i64 a[N], ans;
i64 maxn, G, R, n, T;
int mark[3][N];
bool dfs(int pos, int sum1, int sum2, int mid)
{
	if(sum1 > R || sum2 > G) return false;
	if(pos > n) return true;
	if(mark[1][pos] == mark[2][pos]) {
		if(dfs(mark[1][pos], sum1 + 1, sum2, mid)) return true; 
	}
	else {
		if(dfs(mark[2][pos], sum1, sum2 + 1, mid)) return true;
		if(dfs(mark[1][pos], sum1 + 1, sum2, mid)) return true;
	}
	return false;
}
// the big example used 1500ms
// but when R or G get bigger than 20, it wll die
bool pd(int mid)
{
	for(int i = 1; i <= n; i ++) {
		mark[1][i] = upper_bound(a + 1, a + 1 + n, a[i] + mid - 1) - a;
		mark[2][i] = upper_bound(a + 1, a + 1 + n, a[i] + mid * 2 - 1) - a;
	}
	return dfs(1, 0, 0, mid);
} 
// A magical idea 
// but it can pass all the data I made
vector <int> v;
bool solve(int mid)
{
	for(int i = 1; i <= n; i ++) {
		mark[1][i] = upper_bound(a + 1, a + 1 + n, a[i] + mid - 1) - a;
		mark[2][i] = upper_bound(a + 1, a + 1 + n, a[i] + mid * 2 - 1) - a;
	}
	int pos = 1;
	i64 sum1 = 0;
	v.clear();
	while(pos <= n) {
		v.push_back(pos);
		pos = mark[1][pos];
		sum1 ++;
	}
	if(sum1 <= R) return true;
	// try replace L to 2 * L in order to reduce sum1;
	i64 cnt = 0;
	for(int i = 1; i < (int)v.size(); i ++) {
		if(mark[1][v[i]] <= mark[2][v[i] - 1]) cnt ++;
	}
	cnt = min(cnt, G);
	sum1 -= cnt * 2;
	sum1 -= (G - cnt);
	return (sum1 <= R);
}
int main()
{
	freopen("light.in", "r", stdin);
	freopen("light.out", "w", stdout);
	ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0);
	cin >>n >>R >>G;
	if(R + G >= n) { 
		cout <<"1" <<endl;
		return 0;
	}
	for(int i = 1; i <= n; i ++) {
		cin >>a[i];
		maxn = max(maxn, a[i]);
	}
	sort(a + 1, a + 1 + n);
	i64 ll = 1, rr = maxn; // please notice that ll should begin from 1
	while(rr >= ll) {
		i64 mid = (rr + ll) >> 1;
		if(solve(mid)) ans = mid, rr = mid - 1;
		else ll = mid + 1;
	}
	// maybe n \times log(n)^2
	cout <<ans <<endl;
	return 0;
}

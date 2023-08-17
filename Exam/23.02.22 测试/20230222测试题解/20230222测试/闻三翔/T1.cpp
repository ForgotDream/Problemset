# include <cstdio>
# include <algorithm>
# include <cstring>
# include <iostream>
# include <cmath>
using namespace std;
const int N = 1e6 + 50;
int n, h[N], m, K, ans, len, pos;
struct node {
	int x, y;
	bool operator <(const node &tmp) const {
		if(x == tmp.x) return y < tmp.y;
		return x < tmp.x;
	}
} a[N];
int main()
{
	ios_base::sync_with_stdio,cin.tie(0),cout.tie(0);
	cin >>n >>m >>K;
	for(int i = 1, x, y; i <= K; i ++) {
		cin >>a[i].x >>a[i].y;
	}
	sort(a + 1, a + 1 + K);
	for(int i = 1; i <= K; i ++) {
		int pos = lower_bound(h + 1, h + 1 + len, a[i].y) - h;
		h[pos] = a[i].y;
		len = max(len, pos);
	}
	double ans = (n + m - 2 * len + len * sqrt(2)) * 100;
	int tmp = ans, flag = 0;
	if(ans - tmp >= 0.5) flag = 1;
	cout <<(tmp + flag);
	return 0;
}

# include <cstdio>
# include <iostream>
# include <cstring>
# include <algorithm>
# include <cmath>
using namespace std;
typedef long long i64;
const int N = 2 * 1e5 + 50;
const i64 Inf = 0x3f3f3f3f3f3f3f3f;
const double eps = 1e-4;
template <class T>inline
void Read(T &x)
{
	char ch; x = 0; int base = 1;
	while((ch = getchar()) < '0' || ch > '9') base = (ch == '-') ? -1 : 1;
	x += ch - '0';
	while((ch = getchar()) >= '0' && ch <= '9') x = (x << 1) + (x << 3) + ch - '0';
	x *= base;
	return;
} 
template <typename T>inline
void print(T x)
{
	if(x < 0) {putchar('-'); x = -x;}
	x >= 10 ? (print(x / 10), putchar(x % 10 + '0')) : putchar(x + '0');
	return;
}
int n, limit;
double ans = Inf, mark;
struct line {
	int k, b, t;
	bool operator <(const line &tmp) const {
		if(t == tmp.t) return k > tmp.k;
		else return t < tmp.t;
	}
} p[N];
double calc(double x, int id)
{
	return (double)(p[id].b + p[id].k * x);
}
int main()
{
	freopen("chase.in", "r", stdin);
	freopen("chase.out", "w", stdout);
	Read(n); 
	for(int i = 1, ti, vi; i <= n; i ++) {
		Read(ti); Read(vi);
		p[i].k = vi; 
		p[i].b = ti * vi * -1;
		p[i].t = ti;
		limit = max(limit, ti);
	}
	sort(p + 1, p + 1 + n);
	for(int i = 1; i <= n; i ++) {
		for(int j = i + 1; j <= n; j ++) {
			double maxn = 0, minn = Inf;
			if(fabs(p[i].k - p[j].k) < eps) {
				mark = max(mark, fabs(p[1].b - p[2].b));
				continue;
			}
			double x = (double)(p[i].b - p[j].b) / (p[i].k - p[j].k);
			x *= -1;
			if(x < limit) continue;
			for(int k = 1; k <= n; k ++) {
				maxn = max(maxn, calc(x, k));
				minn = min(minn, calc(x, k));
			}
			ans = min(ans, maxn - minn);
		}
	}
	ans = max(ans, mark);
	printf("%.2lf", ans);
	return 0;
} 

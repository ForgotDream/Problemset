# include <cstdio>
# include <iostream>
# include <algorithm>
# include <cstring>
# include <map>
# include <cmath>
using namespace std;
typedef long long i64;
const int N = 500, Inf = 0x3f3f3f3f;
const double eps = 1e-4;
template <class T>inline
void Read(T &x)
{
	char ch; x = 0; int base = 1;
	while((ch = getchar()) < '0' || ch > '9') base = (ch == '-') ? -1 : 1;
	x += ch - '0';
	while((ch = getchar()) >= '0' && ch <= '9') x = (x << 1) + (x << 3) + ch - '0';
	x *= base; return;
}
template <typename T>inline
void print(T x)
{
	if(x < 0) {x = -x; putchar('-');}
	x >= 10 ? (print(x / 10), putchar(x % 10 + '0')) : putchar(x + '0');
	return;
}
int n, m, x0, y0;
struct node {
	int x, y, id;
} A[N];
double g[N][N];
bool pd(int x, int y, int i, int j)
{
	if(A[i].x == A[j].x) {
		return (x == A[i].x);
	}
	double k = (double)(A[i].y - A[j].y) / (double)(A[i].x - A[j].x);
	double b = A[i].y - A[i].x * k;
	if(fabs(x * k + b - y) <= eps) return true;
	return false;
}
int main()
{
	freopen("brazil.in", "r", stdin);
	freopen("brazil.out", "w", stdout);
	Read(x0); Read(y0); Read(n); Read(m);
	A[0].x = x0; A[0].y = y0; A[0].id = 0;
	for(int i = 1; i <= n; i ++) {
		Read(A[i].x); Read(A[i].y);
		for(int j = 0; j < i; j ++) {
			g[i][j] = g[j][i] = 
				sqrt((A[i].x - A[j].x) * (A[i].x - A[j].x) + (A[i].y - A[j].y) * (A[i].y - A[j].y));
			if(j == 0) g[i][j] = g[j][i] = 2 * g[i][j];
		}
	}
	for(int i = 1, x, y; i <= m; i ++) {
		Read(x); Read(y);
		for(int j = 1; j <= n; j ++) {
			for(int k = 1; k < j; k ++) {
				if(pd(x, y, j, k)) {
					g[j][k] = g[k][j] = Inf;
				}
			}
		}
	}
	for(int k = 1; k <= n; k ++) {
		for(int i = 0; i <= n; i ++) {
			for(int j = 0; j <= n; j ++) {
				g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
			} 
		}
	}
	i64 tmp = (int)g[0][1];
	if(g[0][1] - tmp + eps >= 0.5) tmp ++;
	print(tmp);
	return 0;
}  

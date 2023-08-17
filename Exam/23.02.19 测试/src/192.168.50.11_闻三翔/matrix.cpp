# include <cstdio>
# include <cstring>
# include <iostream>
# include <algorithm>
# include <vector>
# include <queue>
# include <set>
using namespace std;
const int N = 100;
template <class T>inline
void Read(T &x)
{
	char ch; x = 0; int base = 1;
	while((ch = getchar())<'0' || ch > '9') if(ch == '-') base = -1;
	x += ch - '0';
	while((ch = getchar())>='0' && ch <='9') x = (x << 1) + (x << 3) + ch - '0';
	x *= base; return;
} 
template <typename T>inline
void print(T x)
{
	if(x < 0) putchar('-'), x = -x;
	x >= 10 ? (print(x / 10), putchar(x % 10 + '0')) : putchar(x + '0');
	return;
} 
int n, m, k1, k2;
int _next[4][2] = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}};
bool vis[N][N];
int main()
{
	freopen("matrix.in", "r", stdin);
	freopen("matrix.out", "w", stdout);
	Read(n); Read(m); Read(k1); Read(k2);
	if(n == 1) print(m / 2 * k2);
	else if(m == 1) print(n / 2 * k1);
	else if(n == m) print((n/2) * min(k1, k2));
	else print(min(k1 * (n / 2), k2 * (m / 2)));
	return 0;
} 

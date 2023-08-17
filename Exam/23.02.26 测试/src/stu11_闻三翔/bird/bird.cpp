# include <cstdio>
# include <algorithm>
# include <cstring>
# include <iostream>
# include <queue>
# include <vector>
using namespace std;
typedef long long i64;
const int N = 2 * 1e6 + 50, Inf = 0x3f3f3f3f;
template <class T>inline
void Read(T &x)
{
	char ch; x = 0;
	while((ch = getchar())<'0' || ch > '9') continue;
	x += ch - '0';
	while((ch = getchar()) >= '0' && ch <= '9') x = (x << 1) + (x << 3) + ch - '0';
	return;
}
template <typename T>inline
void print(T x)
{
	if(x < 0) x = -x, putchar('-');
	x >= 10 ? (print(x / 10), putchar(x % 10 + '0')) : putchar(x + '0');
	return;
}
int n, q, xi, yi, cnt[N];
int max4(int a, int b, int c, int d)
{
	return max(max(a, b), max(c, d));
}
int min4(int a, int b, int c, int d)
{
	return min(min(a, b), min(c, d));
}
int main()
{
	freopen("bird.in", "r", stdin);
	freopen("bird.out", "w", stdout);
	Read(n); Read(q);
	Read(xi); Read(yi);
	for(int i = 1; i <= n; i ++) {
		int x, y, x1, y1;
		Read(x); Read(y); Read(x1); Read(y1);
		if(x > x1) swap(x, x1), swap(y, y1);
		int maxn, minn;
		if(y > y1) {
			int tmp = abs(y - y1);
			maxn = max4(abs(x - xi) + abs(y - yi), abs(x1 - xi) + abs(y1 - yi), 
						abs(x - xi) + abs(y - tmp - yi), abs(x1 - xi) + abs(y1 + tmp - yi));
			minn = min4(abs(x - xi) + abs(y - yi), abs(x1 - xi) + abs(y1 - yi), abs(x - xi) + abs(y - tmp - yi),
					    abs(x1 - xi) + abs(y1 + tmp - yi));
			if(x <= xi && x1 >= xi) minn = min(minn, min(abs(yi - y1), abs(yi - y)));
			if(y1 <= yi && y >= yi) minn = min(minn, min(abs(xi - x1), abs(xi - x)));
			if(x <= xi && y >= yi && x1 >= xi && y1 <= yi) minn = 0;
		} else {
			int tmp = abs(y - y1);
			maxn = max4(abs(x - xi) + abs(y - yi), abs(x1 - xi) + abs(y1 - yi),
				        abs(x - xi) + abs(y + tmp - yi), abs(x1 - xi) + abs(y1 - tmp - yi));
			minn = min4(abs(x - xi) + abs(y - yi), abs(x1 - xi) + abs(y1 - yi),
				        abs(x - xi) + abs(y + tmp - yi), abs(x1 - xi) + abs(y1 - tmp - yi));
			if(x <= xi && x1 >= xi) minn = min(minn, min(abs(yi - y1), abs(yi - y)));
			if(y <= yi && y1 >= yi) minn = min(minn, min(abs(xi - x1), abs(xi - x)));
			if(x <= xi && y <= yi && x1 >= xi && y1 >= yi) minn = 0;
		}
		cnt[minn] ++; cnt[maxn + 1] --;
	} 
	int sum = 0;
	for(int i = 0; i <= N - 50; i ++) {
		sum += cnt[i];
		cnt[i] = sum;
	}
	for(int i = 1, x; i <= q; i ++) {
		Read(x); print(cnt[x]); putchar('\n');
	}
	return 0;
} 

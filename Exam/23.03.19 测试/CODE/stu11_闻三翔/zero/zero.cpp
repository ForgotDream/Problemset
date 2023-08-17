# include <cstdio>
# include <iostream>
# include <cstring>
# include <cmath>
# include <algorithm>
# include <map>
using namespace std;
const int N = 300;
template <class T> inline
void Read(T &x)
{
	char ch; x = 0; int base = 1;
	while((ch = getchar()) < '0' || ch > '9') base = (ch == '-') ? -1 : 1;
	x += ch - '0';
	while((ch = getchar()) >= '0' && ch <= '9') x = (x << 1) + (x << 3) + ch - '0';
	x *= base; return;
} 
template <typename T> inline
void print(T x)
{
	if(x < 0) x = -x, putchar('-');
	x >= 10 ? (print(x / 10), putchar(x % 10 + '0')) : putchar(x + '0');
	return;
}
map <int, bool> mp;
int n;
int a[6][N];
void dfs1(int step, int sum)
{
	if(step == 3) {
		mp[sum] = 1;
		return;
	}
	for(int i = 1; i <= n; i ++) {
		dfs1(step + 1, sum + a[step][i]);
	}
	return;
}
void dfs2(int step, int sum)
{
	if(step == 6) {
		if(mp[0 - sum]) {
			printf("Yes");
			exit(0);
		}
		return;
	}
	for(int i = 1; i <= n; i ++) {
		dfs2(step + 1, sum + a[step][i]);
	}
}
int main()
{
	freopen("zero.in", "r", stdin);
	freopen("zero,out", "w", stdout);
	Read(n);
	for(int i = 1; i <= 5; i ++) {
		for(int j = 1; j <= n; j ++) {
			Read(a[i][j]);
		}
	} 
	dfs1(1, 0);
	dfs2(3, 0);
	printf("No");
	return 0;
}
/*
3
1 -2 9
-1 2 1
-3 5 1
-1 7 6
-4 -1 -7
*/

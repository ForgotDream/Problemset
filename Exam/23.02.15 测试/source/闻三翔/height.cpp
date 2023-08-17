# include <cstdio>
# include <algorithm>
# include <cstring>
# include <iostream>
# include <vector>
using namespace std;
const int Inf = 0x3f3f3f3f, N = 100;
typedef long long i64;
template <class T>inline
void Read(T &x)
{
	char ch; x = 0; int base = 1;
	while((ch = getchar())<'0' || ch >'9') if(ch == '-') base = -1;
	x += ch - '0';
	while((ch = getchar())>='0' && ch <='9') x = (x << 1) + (x << 3) + ch - '0';
	x *= base;
	return;
}
template <typename T>inline
void print(T x)
{
	if(x < 0) putchar('-'), x = -x;
	x >= 10 ? (print(x /10), putchar(x % 10 + '0')) : putchar(x + '0');
	return;
}
vector <int> nums;
i64 dp[20][20][2][2];
i64 dfs(int pos, int pre, int k4, int k13, int flag)
{
	if(pos == -1) return (k4 || k13);
	if(flag && dp[pos][pre][k4][k13] != -1) return dp[pos][pre][k4][k13];
	int x = flag ? 9 : nums[pos];
	i64 res = 0;
	for(int i = 0; i <= x; i ++) {
		res += dfs(pos - 1, i, i == 4 || k4, (pre == 1 && i == 3) || k13, flag || i < x);
	}
	if(flag) dp[pos][pre][k4][k13] = res;
	return res;
}
i64 solve(i64 x)
{
	if(x <= 1) return 0;
	nums.clear();
	while(x) {nums.push_back(x % 10); x /= 10;}
	i64 res = 0;
	for(int i = 0; i <= nums[nums.size() - 1]; i ++) {
		res += dfs(nums.size() - 2, i, i == 4, 0, i < nums[nums.size() - 1]);
	}
	return res;
}
i64 K, R, T;
int main()
{
	freopen("height.in", "r", stdin);
	freopen("height.out", "w", stdout);
	Read(T); memset(dp, -1, sizeof(dp));
	while(T --) {
		Read(R); Read(K);
		print((R - solve(R)) * K);
		putchar('\n');
	}
	return 0;
}

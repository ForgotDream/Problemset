# include <cstdio>
# include <iostream>
# include <cstring>
# include <algorithm>
# include <vector>
using namespace std;
const int N = 1e5 + 50;
template <class T>inline
void Read(T &x)
{
	char ch; x = 0; int base = 1;
	while((ch = getchar()) < '0' || ch > '9') if(ch == '-') base = -1;
	x += ch - '0';
	while((ch = getchar()) >='0' && ch <= '9') x = (x << 1) + (x << 3) + ch - '0';
	x *= base; return;
}
template <typename T>inline
void print(T x)
{
	if(x < 0) putchar('-'), x = -x;
	x >= 10 ? (print(x/10), putchar(x % 10 + '0')) : putchar(x + '0');
	return;
}
int dp[50][50], D, n, I;
vector <int> nums;
int dfs(int pos, int sum, int flag)
{
	if(pos < 0) return (sum > D);
	if(flag && dp[pos][sum] != -1) return dp[pos][sum]; 
	int res = 0;
	int x = flag ? 1 : nums[pos];
	for(int i = 0; i <= x; i ++) {
		res += dfs(pos - 1, sum + i, i < x || flag);
	}
	if(flag) dp[pos][sum] = res;
	return res;
} 
int solve(int x)
{
	nums.clear();
	while(x) {nums.push_back(x % 2); x /= 2;}
	int res = 0;
	for(int i = 0; i <= nums[nums.size() - 1]; i ++) {
		res += dfs(nums.size() - 2, i, i < nums[nums.size() - 1]);
	}
	return res;
}
int main()
{
	freopen("bits.in", "r", stdin);
	freopen("bits.out", "w", stdout);
	memset(dp, -1, sizeof(dp));
	Read(n); Read(D); Read(I);
	int k, res = 0; solve(n);
	while(1) {
		k = solve(I + res);
		k -= res; res += k;
		if(k == 0) break;
	}
	I += res; I --;
	nums.clear();
	while(I) {nums.push_back(I % 2); I /= 2;}
	for(int i = n; i >= (int)nums.size() + 1; i --) print(0);
	for(int i = (int)nums.size() - 1; i >= 0; i --) {
		print(nums[i]);
	}
	return 0;
} 

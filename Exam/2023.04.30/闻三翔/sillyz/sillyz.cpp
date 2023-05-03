# include <cstdio>
# include <iostream>
# include <algorithm>
# include <cstring>
# include <vector>
# include <map>
# include <cmath>
using namespace std;
typedef long long i64;
const int N = 1e6 + 50;
i64 L, R;
vector <int> nums;
int dfs(int pos, i64 sum, bool flag, i64 p, i64 k)
{// 1e12
	if(pos < 0) {
		return (sum * p <= k);
	}
 	int x = flag ? 9 : nums[pos];
	i64 res = 0;
	for(int i = 0; i <= x; i ++) {
		if(p == 0 && i != 0) {
			sum = 1;
		}
		if(p != 0 && i == 0) continue;  
		i64 tmp = sum * i * (p * 10 + i) * pow(10, pos);
		if(tmp > k || tmp < 0) break;
		res += dfs(pos - 1, sum * i, i < x || flag, p * 10 + i, k);
	}
	return res;
}
i64 solve(i64 x)
{
	nums.clear();
	i64 tmp = x;
	if(x <= 0) return 0;
	while(x) {nums.push_back(x % 10), x /= 10;}
	//i64 res = 0;
	return dfs(nums.size() - 1, 0, true, 0, tmp);
}
int main()
{
	freopen("sillyz.in", "r", stdin);
	freopen("sillyz.out", "w", stdout);
	cin >>L >>R;
	cout <<solve(R) - solve(L - 1) <<endl;
	return 0;
}

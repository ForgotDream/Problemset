/**
 * @file    P3413 SAC#1 - 萌数.cpp
 * @author  ForgotDream
 * @brief   数位 DP
 * @date    2023-02-13
 */
#include <algorithm>
#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

static const int N = 1e4 + 50;
static const i64 MOD = 1e9 + 7;
string l, r;
int nums[N], d;
i64 f[N][15][15][2];

i64 dfs(int cur, int nxt, int nxnxt, bool limited, bool have) {
	// if (cur == 39) cout << "woshishabi" << '\n';
	// cerr << nxt << ' ' << nxnxt << ' ' << cur << '\n';
	if (!cur) return have;
	if (!limited && ~f[cur][nxt][nxnxt][have]) return f[cur][nxt][nxnxt][have];

	i64 res = 0;
	int up = limited ? nums[cur] : 9;

	for (int i = 0; i <= up; i++) 
		res = (res + dfs(cur - 1, i, nxt, limited && (i == up), have || (i == nxt) || (i == nxnxt))) % MOD;

	if (!limited) f[cur][nxt][nxnxt][have] = res;
	return res;
}

i64 calc(string str) {
	i64 res = 0;
	int len = str.length() - 1;
	static int d = 0;
	memset(f, -1, sizeof(f));

	for (int i = 1; i <= len; i++) nums[i] = str[i] - '0';

	// 进位操作
	nums[1] += d;
	if (len == 1 && nums[1] <= 0) return 0;
	for (int i = 1; nums[i] < 0 && i <= len; i++) 
		nums[i] += 10, nums[i + 1] -= 1;
	while (len && !nums[len]) len--;

	// for (int i = len; i >= 1; i--) cerr << nums[i];
	// cerr << '\n';

	for (int i = 1; i < len; i++)
		for (int j = 1; j <= 9; j++)
			res = (res + dfs(i - 1, j, 10, 0, 0)) % MOD;
	
	// 单独处理最高位
	for (int i = 1; i <= nums[len]; i++)
		res = (res + dfs(len - 1, i, 10, i == nums[len], 0)) % MOD;

	return d--, res;
}

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

	cin >> l >> r;
	reverse(l.begin(), l.end()), reverse(r.begin(), r.end());
	
	l = "0" + l, r = "0" + r;

	cout << ((calc(r) - calc(l)) % MOD + MOD) % MOD << '\n';
	return 0;
}
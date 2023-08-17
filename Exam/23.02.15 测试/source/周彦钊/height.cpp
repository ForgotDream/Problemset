#include <iostream>
#include <iomanip>
#include <cstring>

using namespace std;
using i64 = long long;

static const int N = 20;
int T;
i64 a, b;
int len, nums[N];
int f[N][N][N][2];

i64 dfs(int pos, int cur, int pre, bool has4, bool isLimited) {
	if (has4 || (cur == 3 && pre == 1)) return 0; 
	if (!pos) return 1;
	if (!isLimited && ~f[pos][cur][pre][has4]) return f[pos][cur][pre][has4];
	
	i64 res = 0;
	int up = isLimited ? nums[pos] : 9;
	// cout << up << '\n';
	for (int i = 0; i <= up; i++) {
		res += dfs(pos - 1, i, cur, has4 || i == 4, isLimited && i == up);
	}
	
	if (!isLimited) f[pos][cur][pre][has4] = res;
	return res;
}

i64 calc(i64 num) {
	if (!num) return 0;
	memset(f, -1, sizeof(f));
	i64 res = 0;
	len = 0;
	while (num) nums[++len] = num % 10, num /= 10;
	
	for (int i = 1; i < len; i++)
		for (int j = 1; j <= 9; j++) {
			res += dfs(i - 1, j, 11, j == 4, 0);
			// cout << res << ' ' << i << ' ' << j << '\n';
		}
		
	for (int i = 1; i <= nums[len]; i++) res += dfs(len - 1, i, 11, i == 4, i == nums[len]);
	
	return res;
}

int main() {
	freopen("height.in", "r", stdin);
	freopen("height.out", "w", stdout);
	
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	
	cin >> T;
	while (T--) {
		cin >> a >> b;
		cout << calc(a) * b << '\n';
		// calc(a);
	}	
	
	return 0;
}

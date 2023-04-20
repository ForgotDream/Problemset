/**
 * @file    P2696 慈善的约瑟夫.cpp
 * @author  ForgotDream
 * @brief   递推
 * @date    2023-02-12
 */
#include <bits/stdc++.h>

using namespace std;
using i64 = long long;
using i128 = __int128;

static const int N = 100050, MOD = 10000;
int n, ans;
queue<int> q;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

	cin >> n;
	
	ans = n;
	while (true) {
		for (int i = 1; i <= n; i++) q.push(i);
		for (int i = 1; i < n; i++) {
			q.push(q.front());
			q.pop(), q.pop();
		}
		int lst = q.front();
		if (n == lst) {
			ans += lst;
			break;
		}
		n = lst, q.pop();
	}

	cout << ans << '\n';
	return 0;
}
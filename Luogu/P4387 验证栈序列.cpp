/**
 * @file    P4387 验证栈序列.cpp
 * @author  ForgotDream
 * @brief   栈 + 模拟
 * @date    2023-02-13
 */
#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

static const int N = 1e5 + 50, MOD = 10000;
int q, n;
int a[N], b[N], cnt;
stack<int> st;

inline void init() {
	cnt = 1;
	while (!st.empty()) st.pop();
	return;
}

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

	cin >> q;

	while (q--) {
		init();

		cin >> n;
		for (int i = 1; i <= n; i++) cin >> a[i];
		for (int i = 1; i <= n; i++) cin >> b[i];

		for (int i = 1; i <= n; i++) {
			st.push(a[i]);

			while (st.top() == b[cnt]) {
				st.pop(), cnt++;
				if (st.empty()) break;
			}
		}

		if (st.empty()) cout << "Yes" << '\n';
		else cout << "No" << '\n';
	}

	return 0;
}
/**
 * @file    P1739 表达式括号匹配.cpp
 * @author  ForgotDream
 * @brief   栈
 * @date    2023-02-13
 */
#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

static const int N = 1e4 + 50;
string s;
stack<bool> st;

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

	cin >> s;

	for (int i = 0; i < s.length(); i++) {
		if (s[i] == ')') {
			if (st.empty()) return cout << "NO" << '\n', 0;
			else st.pop();
		} else if (s[i] == '(') st.push(1);
	}

	if (st.empty()) cout << "YES" << '\n';
	else cout << "NO" << '\n';
	return 0;
}
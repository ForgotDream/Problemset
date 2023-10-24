/**
 * @file    P1981 表达式求值.cpp
 * @author  ForgotDream
 * @brief   栈
 * @date    2023-02-13
 */
#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

static const int N = 1e4 + 50, MOD = 10000;
string s;
stack<int> st;
i64 num, tmp, ans;
char opt;

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

	cin >> num, num %= MOD;
	st.push(num);
	while (cin >> opt >> num) {
		if (opt == '*') tmp = st.top(), st.pop(), st.push(tmp * num % MOD);
		else st.push(num);
	}

	while (!st.empty()) 
		(ans += st.top()) %= MOD, st.pop();	
	
	cout << ans << '\n';
	return 0;
}
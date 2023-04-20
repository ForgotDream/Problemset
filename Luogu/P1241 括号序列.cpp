/**
 * @file    P1241 括号序列.cpp
 * @author  ForgotDream
 * @brief   栈的思想
 * @date    2023-02-13
 */
#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

static const int N = 1e5 + 50, MOD = 10000;
string s;
bool check[N];

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

	cin >> s;

	for (int i = 0; i < s.length(); i++) {
		if (s[i] == ')') 
			for (int j = i - 1; ~j; j--) {
				if (s[j] == '(' && !check[j]) {
					check[i] = check[j] = true;
					break;
				} else if (s[j] == '[' && !check[j]) break;
			}
		else if (s[i] == ']')
			for (int j = i - 1; ~j; j--) {
				if (s[j] == '[' && !check[j]) {
					check[i] = check[j] = true;
					break;
				} else if (s[j] == '(' && !check[j]) break;
			}
	}

	for (int i = 0; i < s.length(); i++) {
		if (!check[i]) {
			if (s[i] == '[' || s[i] == ']') cout << "[]";
			else cout << "()";
		} else cout << s[i];
	}

	return 0;
}
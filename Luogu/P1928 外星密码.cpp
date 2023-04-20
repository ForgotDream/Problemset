/**
 * @file    P1928 外星密码.cpp
 * @author  ForgotDream
 * @brief   递归
 * @date    2023-02-14
 */
#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

static const int N = 5e4 + 50, MOD = 1e5 + 3;
string str;

string solve(string cur, bool isFirst = true) {
	string res = "";
	int pivot = 1, t = 0;
	for (int i = 0; i < cur.length(); i = pivot) {
		bool flg = true;
		if (i < 2 && !isFirst) {
			if (isdigit(cur[i])) t = 10 * t + cur[i] - '0', flg = false;
		}
		pivot = i + 1;
		if (cur[i] == '[') {
			int cnt = 1;
			for (; pivot < cur.length() && cnt; pivot++) {
				if (cur[pivot] == '[') cnt++;
				else if (cur[pivot] == ']') cnt--;
			}
			res += solve(cur.substr(i + 1, pivot - i - 2), false);
		}
		else if (flg) res += cur[i];
		// cerr << i << ' ' << pivot << '\n';
	}
	if (!isFirst) {
		string tmp = res;
		while (t != 1) res += tmp, t--;
	}
	return res;
}

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	
	cin >> str;
	cout << solve(str) << '\n';

	return 0;
}
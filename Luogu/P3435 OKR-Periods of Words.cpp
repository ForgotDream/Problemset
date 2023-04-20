/**
 * @file 	P3435 OKR-Periods of Words.cpp
 * @author 	ForgotDream
 * @brief 	KMP + DP
 * @date 	2023-02-02
 */

#include <bits/stdc++.h>

using namespace std;
using i64 = long long;
using i64u = unsigned long long;
using i128 = __int128;

const int N = 1e6 + 50;
int n;
string str;
int fail[N];
i64 ans;

void init() {
	for (int i = 2, j = 0; i <= str.length(); i++) {
		while (j && str[i] != str[j + 1]) j = fail[j];
		j += (str[i] == str[j + 1]);
		fail[i] = j;
	}
	return;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	
	cin >> n >> str;
	str = "0" + str;

	init();

	for (int i = 2, j; i <= str.length(); i++) {
		j = i;
		while (fail[j]) j = fail[j];
		if (fail[i]) fail[i] = j;
		ans += i - j;
	}

	cout << ans << endl;
	return 0;
}
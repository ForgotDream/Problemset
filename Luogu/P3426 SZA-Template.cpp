/**
 * @file 	P3426 SZA-Template.cpp
 * @author 	ForgotDream
 * @brief 	KMP + DP
 * @date 	2023-02-01
 */

#include <bits/stdc++.h>

using namespace std;
using i64 = long long;
using i64u = unsigned long long;
using i128 = __int128;

const int N = 5e5 + 50;
char str[N];
int len, fail[N];
int f[N], bucket[N];

void init() {
	fail[0] = -1;
	for (int i = 2, j = 0; i <= len; i++) {
		while (j != -1 && str[i] != str[j + 1]) j = fail[j];
		fail[i] = ++j;
	}
	return;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	
	cin >> (str + 1);
	len = strlen(str + 1);

	init();

	bucket[1] = f[1] = 1;
	for (int i = 2; i <= len; i++) {
		f[i] = i;
		if (bucket[f[fail[i]]] >= i - fail[i]) f[i] = f[fail[i]];
		bucket[f[i]] = i;
	}

	cout << f[len] << '\n';
	return 0;
}
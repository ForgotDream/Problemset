/**
 * @file 	P4824 Censoring S.cpp
 * @author 	ForgotDream
 * @brief 	KMP
 * @date 	2023-02-01
 */

#include <bits/stdc++.h>

using namespace std;
using i64 = long long;
using i64u = unsigned long long;
using i128 = __int128;

const int N = 1e6 + 50;
char s[N], t[N];
int lenS, lenT;
int st[N], top;
int fail[N], pre[N];

void init() {
	fail[0] = fail[1] = 0;
	for (int i = 2, j = 0; i <= lenT; i++) {
		while (j && t[i] != t[j + 1]) j = fail[j];
		j += (t[i] == t[j + 1]);
		fail[i] = j;
	}
	return;
}

void kmp() {
	for (int i = 1, j = 0; i <= lenS; i++) {
		while (j && s[i] != t[j + 1]) j = fail[j];
		j += (s[i] == t[j + 1]);
		pre[i] = j, st[++top] = i;
		if (j == lenT) 
			top -= lenT, j = pre[st[top]];
	}
	return;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	
	cin >> (s + 1) >> (t + 1);
	lenS = strlen(s + 1), lenT = strlen(t + 1);

	init();
	kmp();

	for (int i = 1; i <= top; i++) cout << s[st[i]];
	cout << '\n';
	return 0;
}
/**
 * @file 	P3193 GT考试.cpp
 * @author 	ForgotDream
 * @brief 	Matrix + KMP
 * @date 	2023-02-02
 */

#include <bits/stdc++.h>

using namespace std;
using i64 = long long;
using i64u = unsigned long long;
using i128 = __int128;

const int N = 1e6 + 50;
int n, m, mod;
struct mat {
	int row, col;
	int arr[105][105];

	mat() { memset(arr, 0, sizeof(arr)); }
	mat(int x, int y) {
		row = x, col = y;
		memset(arr, 0, sizeof(arr));
	}

	void init() {
		for (int i = 1; i <= row; i++)
			arr[i][i] = 1;
		return;
	}

	void print() {
		for (int i = 1; i <= row; i++)
			for (int j = 1; j <= col; j++)
				cerr << arr[i][j] << (j == col ? '\n' : ' ');
		cerr << '\n';
		return;
	}

	void operator= (const mat& b) {
		for (int i = 1; i <= row; i++)
			for (int j = 1; j <= col; j++)
				arr[i][j] = b.arr[i][j];
		return;
	}

	mat operator* (const mat& b) const {
		mat res(row, b.col);
		for (int i = 1; i <= row; i++)
			for (int j = 1; j <= b.col; j++)
				for (int k = 1; k <= col; k++)
					res.arr[i][j] = (res.arr[i][j] + (i64) arr[i][k] * b.arr[k][j] % mod) % mod;
		return res;
	}

	mat operator^ (int p) const {
		mat res(row, col), base(row, col);
		res.init();
		base = (*this);
		while (p) {
			if (p & 1) res = res * base;
			base = base * base;
			p >>= 1;
		}
		return res;
	}
} g;
int fail[N], ans;
string t;

void init() {
	for (int i = 2, j = 0; i <= m; i++) {
		while (j && t[i] != t[j + 1]) j = fail[j];
		j += (t[i] == t[j + 1]);
		fail[i] = j;
	}
	return;
}

void kmp() {
	for (int i = 0, j; i < m; i++)
		for (char ch = '0'; ch <= '9'; ch++) {
			j = i;
			while (j && ch != t[j + 1]) j = fail[j];
			j += (t[j + 1] == ch);
			g.arr[i + 1][j + 1] = (g.arr[i + 1][j + 1] + 1) % mod;
		}
	return;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

	cin >> n >> m >> mod;
	cin >> t, t = '0' + t;

	g.row = g.col = m;

	init();
	kmp();

	mat f(1, m);
	f.arr[1][1] = 1;
	g = (g ^ n);
	f = (f * g);

	for (int i = 1; i <= m; i++) ans = (ans + f.arr[1][i]) % mod;

	cout << ans << '\n';
	return 0;
}
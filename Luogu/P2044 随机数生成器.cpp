/**
 * @file P2044 随机数生成器.cpp
 * @author ForgotDream
 * @brief 矩阵加速递推 + 龟速乘（可能），但是 `i128` 能过
 * @date 2023-01-29
 */

#include <bits/stdc++.h>

namespace FastIO {
	template<typename T>
	inline void read(T& x) {
		x = 0;
		T f = 1;
		char c = getchar();
		while (!isdigit(c)) {
			if (c == '-') f = -1;
			c = getchar();
		}
		while (isdigit(c)) x = x * 10 + c - '0', c = getchar();
		x *= f;
		return;
	}

	template<typename T, typename ... args>
	inline void read(T& x, args& ... tmp) {
		read(x);
		read(tmp...);
		return;
	}

	template<typename T>
	inline void print(T x) {
		if (x < 0) putchar('-'), x = -x;
		if (x / 10) print(x / 10);
		putchar(x % 10 + '0');
		return;
	}

	template<typename T>
	inline void print(T x, char c) {
		print(x), putchar(c);
		return;
	}
}

using namespace std;
using namespace FastIO;
using i64 = long long;
using i128 = __int128;

i128 m, a, c, x, n, g;
struct Mat {
	int row, col;
	i128 arr[105][105];

	Mat() { memset(arr, 0, sizeof(arr)); }
	Mat(int x, int y) {
		row = x, col = y;
		memset(arr, 0, sizeof(arr));
	}

	void init() {
		for (int i = 1; i <= row; i++)
			arr[i][i] = 1;
		return;
	}

	void operator= (const Mat& b) {
		for (int i = 1; i <= row; i++)
			for (int j = 1; j <= col; j++)
				arr[i][j] = b.arr[i][j];
		return;
	}

	Mat operator* (const Mat& b) const {
		Mat res(row, b.col);
		for (int i = 1; i <= row; i++)
			for (int j = 1; j <= b.col; j++)
				for (int k = 1; k <= col; k++)
					res.arr[i][j] = (res.arr[i][j] + (i128)arr[i][k] * (i128)b.arr[k][j]) % m;
		return res;
	}

	Mat operator^ (i64 p) const {
		Mat res(row, col), base(row, col);
		res.init();
		base = (*this);
		while (p) {
			if (p & 1) res = res * base;
			base = base * base;
			p >>= 1;
		}
		return res;
	}
};

int main() {
	read(m, a, c, x, n, g);

	if (!n) return print(x, '\n'), 0;

	Mat p(4, 4), b(2, 1);
	p.arr[1][1] = a, p.arr[1][2] = 1, p.arr[2][2] = 1;
	b.arr[1][1] = x, b.arr[2][1] = c;

	p = p ^ n;
	p = p * b;

	print(p.arr[1][1] % g, '\n');
	return 0;
}
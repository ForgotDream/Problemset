// #include <bits/stdc++.h>
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

typedef long long ll;

int n, m;
const int M = 105, MOD = (int)1e8;
struct mat {
    int row, col;
    int arr[M][M];

    mat() { memset(arr, 0, sizeof(arr)); }
    mat(int x, int y) {
        row = x, col = y;
        memset(arr, 0, sizeof(arr));
    }

    void print() {
        for (int i = 1; i <= row; i++)
            for (int j = 1; j <= col; j++)
                cout << arr[i][j] << (j == col ? '\n' : ' ');
        return;
    }

    void init() {
        for (int i = 1; i <= row; i++)
            arr[i][i] = 1;
        return;
    }

    void operator= (const mat& b) {
        for (int i = 1; i <= row; i++)
            for (int j = 1; j <= col; j++)
                arr[i][j] = b.arr[i][j];
        return;
    }

    mat operator+ (const mat& b) const {
        mat res(row, col);
        for (int i = 1; i <= row; i++)
            for (int j = 1; j <= col; j++)
                res.arr[i][j] = ((ll)arr[i][j] + (ll)b.arr[i][j]) % MOD;
        return res;
    }

    mat operator* (const mat& b) const {
        mat res(row, b.col);
        for (int i = 1; i <= row; i++)
            for (int j = 1; j <= b.col; j++)
                for (int k = 1; k <= col; k++)
                    res.arr[i][j] = (res.arr[i][j] + (ll)arr[i][k] * (ll)b.arr[k][j]) % MOD;
        return res;
    }

    mat operator^ (ll p) const {
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
};

int gcd(int a, int b) {
	return b ? gcd(b, a % b) : a;
}

void solve() {
	int gcd_num = gcd(n, m);
	mat a(1, 2), d(2, 2);
	a.arr[1][1] = 1, a.arr[1][2] = 1;
	d.arr[1][1] = 0, d.arr[1][2] = 1;
	d.arr[2][1] = 1, d.arr[2][2] = 2;
    if (gcd_num == 1) {
        cout << 1 << endl;
        return;
    }
	a = (a * (d ^ (gcd_num - 2)));
	cout << a.arr[1][2] << endl;
	return;
}

int main() {
	// cin >> n >> m;
	solve();
	return 0;
}
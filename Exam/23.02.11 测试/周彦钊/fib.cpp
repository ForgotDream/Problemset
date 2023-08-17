#include <iostream>
#include <cstring>

using namespace std;
using i64 = long long;
using i64u = unsigned long long;

static const int N = 25;
i64 n;
int m;
int d[N]; 

struct Matrix {
	int row, col;
	int a[N][N];
	
	void init(bool isEmpty = true) {
		if (isEmpty) row = 0, col = 0;
		memset(a, 0, sizeof a);
		return;
	}
	
	Matrix() { init(); }
	Matrix(int n, int m) : row(n), col(m) { init(0); }
	
	void unify() {
		for (int i = 1; i <= row; i++)
			a[i][i] = 1;
		return;
	}
	
	int* operator[](int i) {
		return a[i];
	}
	
	Matrix operator=(const Matrix &oth) {
		for (int i = 1; i <= row; i++)
			for (int j = 1; j <= col; j++)
				a[i][j] = oth.a[i][j];
		return (*this);
	}
	
	Matrix operator*(const Matrix &oth) const {
		Matrix res(row, oth.col);
		
		for (int i = 1; i <= row; i++)
			for (int j = 1; j <= oth.col; j++)
				for (int k = 1; k <= col; k++) {
					res.a[i][j] = ((i64) res.a[i][j] + (i64) (a[i][k] * oth.a[k][j]) % m) % m;
				}
			
		return res;
	}
};

Matrix fastPow(Matrix base, i64 p, int mod) {
	Matrix res(base.row, base.col);
	res.unify();
	
	while (p) {
		if (p & 1) res = res * base;
		base = base * base;
		p >>= 1;
	}
	
	return res;
}

int main() {
	freopen("fib.in", "r", stdin);
	freopen("fib.out", "w", stdout);
	
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	
	cin >> n >> m;
	
	Matrix a(1, 2), b(2, 2);
	
	a[1][1] = 1, a[1][2] = 1;
	b[1][1] = 0, b[1][2] = 1;
	b[2][1] = 1, b[2][2] = 1;
	
	b = fastPow(b, n, m);
	cout << (a * b)[1][1] << '\n';
	
	return 0;
}

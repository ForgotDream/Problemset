#include <iostream>
#include <cstdio>

using namespace std;

const int M = 1e5;
int n, W;
int v[M + 50], w[M + 50], t[M + 50];
int f[M + 50];

void _01(int vi, int wi) {
	for (int j = W; j >= wi; j--) f[j] = max(f[j], f[j - wi] + vi);
	return;
}

void _comp(int vi, int wi) {
	for (int j = wi; j <= W; j++) f[j] = max(f[j], f[j - wi] + vi);
	return;
}

void solve(int vi, int wi, int ti) {
	if (wi * ti >= W) {
		_comp(vi, wi);
		return;
	}
	for (int k = 1; k <= ti; k <<= 1) {
		_01(vi * k, wi * k);
		ti -= k;
	}
	if (ti > 0) _01(vi * ti, wi * ti);
	return;
}

int main() {
	cin >> n >> W;
	for (int i = 1; i <= n; i++) {
		cin >> v[i] >> w[i] >> t[i];
		solve(v[i], w[i], t[i]);
	}
	cout << f[W] << endl;
	return 0;
}
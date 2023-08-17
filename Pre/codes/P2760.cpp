#include <iostream>
#include <cstdio>

using namespace std;

int n, m, ti, a;
int l1[105][105];
int l2[105][105];
int v[10050], w[10050], t[10050], cnt;
int f[150];

void _01(int vi, int wi) {
	for (int j = a; j >= wi; j--) f[j] = max(f[j], f[j - wi] + vi);
	return;
}

void _comp(int vi, int wi) {
	for (int j = wi; j <= a; j++) f[j] = max(f[j], f[j - wi] + vi);
	return;
}

void _mul(int vi, int wi, int ti) {
	if (wi * ti >= a) {
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

void solve() {
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			if (l1[i][j] && l2[i][j])
				t[++cnt] = l2[i][j], v[cnt] = l1[i][j], w[cnt] = 2 * (i + j);
	for (int i = 1; i <= cnt; i++)
		_mul(v[i], w[i], t[i]);
	cout << f[a] << endl;
	return;
}

int main() {
	cin >> n >> m >> ti >> a;
	a--;
	a = min(a, ti);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			cin >> l1[i][j];
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			cin >> l2[i][j];
	solve();
	return 0;
}
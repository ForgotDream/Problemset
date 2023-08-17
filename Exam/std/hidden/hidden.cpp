#include <cstdio>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 1e6 + 7;

int n;
int a[N];
int b[N];
int c[N];
int d[N];
int tax[N];

int main()
{
	freopen("hidden.in", "r", stdin);
	freopen("hidden.out", "w", stdout);

	string p;

	cin >> p;

	n = p.length();
	for(int i = 0; i < n; ++ i)
		if(p[i] >= 'A') a[i] = p[i] - 'A' + 1;
		else a[i] = 0;

	for(int i = 0; i < n; ++ i) tax[a[i]] ++;
	for(int i = 1; i < 30; ++ i) tax[i] += tax[i-1];
	for(int i = n - 1; i >= 0; -- i) b[i] = --tax[a[i]];
	for(int i = 0; i < n; ++ i) d[b[i]] = i;

	for(int i = 0, t = d[0]; i < n; ++ i)
		c[i] = t, t = d[t];

	for(int i = 0; i < n-1; ++ i)
		cout << char(a[d[c[i]]] + 'A' - 1);
	cout << ".\n" << endl;

	return 0;
}

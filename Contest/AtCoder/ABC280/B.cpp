#include <iostream>
#include <cstdio>

using namespace std;

int n;
int a[50];

int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		cout << a[i] - a[i - 1] << ' ';
	}
	return 0;
}
#include <iostream>
#include <cstdio>

using namespace std;

int n;
int a, b, tmp;

int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> tmp;
		if (tmp > a) a = tmp, b = i;
	}
	cout << b << endl;
	return 0;
}
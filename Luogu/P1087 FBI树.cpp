#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

int n;
char ch[1500];

template<class T>
void read(T& x) {
	int flag = 1;
	x = 0;
	char c = getchar();
	while (c < '0' || c > '9') {
		if (c == '-')
			flag = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9') {
		x = (x << 3) + (x << 1) + (c ^ '0');
		c = getchar();
	}
	x *= flag;
	return;
}

int solve(int l, int r) {
	if (l == r) {
		if (ch[l] == '0') {
			putchar('B');
			return 1;
		} else {
			putchar('I');
			return 2;
		}
	}
	int mid = (l + r) / 2;
	int ans1 = solve(l, mid), ans2 = solve(mid + 1, r);
	if (ans1 == 3 || ans2 == 3 || ans1 + ans2 == 3) {
		putchar('F');
		return 3;
	} 
	if (ans1 == 1 && ans2 == 1) {
		putchar('B');
		return 1;
	} 
	if (ans1 == 2 && ans2 == 2) {
		putchar('I');
		return 2;
	}
}

int main() {
	read(n);
	cin >> ch;
	solve(0, (1 << n) - 1);
	return 0;
}
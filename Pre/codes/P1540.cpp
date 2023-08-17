#include <iostream>
#include <cstdio>
#include <queue>

using namespace std;

int m, n, ans, tmp;
int head, tail;
int q[1005];

int main() {
	cin >> m >> n;
	for (int i = 1; i <= n; i++) {
		while (tail - head > m) head++;
		bool flag = true;
		cin >> tmp;
		for (int j = head + 1; j <= tail; j++)
			if (q[j] == tmp) {
				flag = false;
				break;
			}
		if (flag) {
			q[++tail] = tmp, ans++;
		}
		while (tail - head > m) head++;
	}
	cout << ans << endl;
	return 0;
}
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

char mid[100], aft[100];

void solve(int ml, int mr, int al, int ar) {
	if (ml > mr || al > ar) return;
	cout << aft[ar];
	for (int i = ml; i <= mr; i++) {
		if (mid[i] == aft[ar]) {
			solve(ml, i - 1, al, al + i - ml - 1);
			solve(i + 1, mr, al + i - ml, ar - 1);
			break;
		}
	}
}

int main() {
	cin >> mid >> aft;
	solve(0, strlen(mid) - 1, 0, strlen(aft) - 1);
	cout << endl;
	return 0;
}
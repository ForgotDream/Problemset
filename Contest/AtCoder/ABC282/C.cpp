#include <iostream>
#include <cstdio>

using namespace std;

const int N = 2e5 + 50;
int n, cnt;
char s[N];

int main() {
	cin >> n >> (s + 1);
	for (int i = 1; i <= n; i++) {
		if (s[i] == '"') cnt++;
		else if (s[i] == ',') if (!(cnt % 2)) s[i] = '.';
	}
	cout << s + 1 << endl;
	return 0;
}
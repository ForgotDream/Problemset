#include <bits/stdc++.h>

using namespace std;

const int N = 150;
int n, k;
string str[N];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	
	cin >> n >> k;
	for (int i = 1; i <= n; i++) cin >> str[i];

	sort(str + 1, str + k + 1);

	for (int i = 1; i <= k; i++) cout << str[i] << '\n';
	return 0;
}
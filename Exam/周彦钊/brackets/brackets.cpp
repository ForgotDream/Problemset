#include <iostream>
#include <cstdio>
#include <string>
#include <stack>

using namespace std;

int t, n;
string str;
stack<char> st;

bool check(string tmp) {
	while(!st.empty()) st.pop();
	bool flag = false;
	for (int i = 0; i < tmp.length(); i++) {
		if (tmp[i] == '(') st.push('('), flag = true;
		else {
			if (!st.empty()) st.pop();
			else return false;
		}
	}
	return st.empty() && flag;
}

void solve() {
	if (check(str)) {
		cout << "possible" << endl;
		return;
	}
	for (int len = 1; len < n; len++) {
		for (int l = 0; l + len - 1 < n; l++) {
			string tmp = str;
			// cout << tmp << endl;
			int r = l + len - 1;
			for (int k = l; k <= r; k++) {
				if (tmp[k] == '(') tmp[k] = ')';
				else tmp[k] = '(';
			}
			// cout << tmp << endl;
			if (check(tmp)) {
				cout << "possible" << endl;
				return;
			}
		}
	}
	cout << "impossible" << endl;
	return;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	
	freopen("brackets.in", "r", stdin);
	freopen("brackets.out", "w", stdout);
	
	cin >> t;
	while (t--) {
		cin >> str;
		n = str.length();
		solve();
	}
	return 0;
}

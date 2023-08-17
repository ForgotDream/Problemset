#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

char str[30050];
int len;
int suc[30050], pre[30050];

struct node {
	int no;
	char ch;
} a[30050], b[30050];

bool cmp(const node& a, const node& b) {
	if (a.ch != b.ch) return a.ch < b.ch;
	else return a.no < b.no;
}

void solve() {
	for (int i = 0; i < len; i++) {
		a[i].no = i, a[i].ch = str[i];
		b[i].no = i, b[i].ch = str[i];
	}
	sort(b, b + len, cmp);
	
	for (int i = 0; i < len; i++) {
		suc[i] = b[i].no;
		pre[b[i].no] = i;
	}
	
	int k = suc[0];
	for (int i = 1; i < len; i++) {
		k = suc[k];
		cout << str[k];
	}
	cout << '.' << endl;
	return;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	
	freopen("hidden.in", "r", stdin);
	freopen("hidden.out", "w", stdout);
	
	cin >> str;
	len = strlen(str);
	
	solve();
	
	return 0;
}

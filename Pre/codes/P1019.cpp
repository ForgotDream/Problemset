#include <iostream>
#include <cstdio>
#include <string>

using namespace std;

string s[50];
int n, Ans;
char st;
bool used[50];

int contact (string a, string b) {
	string c;
	int i;
	for(i = 1; i<=min(a.length(), b.length()); i++) {
		if(a.substr(a.length() - i, a.length())==b.substr(0, i)) break;
	}
	if(i!=min(a.length(), b.length())+1) {
		c = a.substr(0, a.length() - i) + b;
		return c.length() - a.length();
	} else return 0;
}

void dfs (string Str, int Sum, int step = 1) {
	Ans = max(Ans, Sum);
	if(step==2*n) {
		Ans = max(Ans, Sum);
		return;
	}
	for(int i = 1; i<=2*n; i++) {
		int j = contact(Str, s[i]);
		if(j&&!used[i]) {
			used[i] = true;
			dfs(s[i], Sum+j, step+1);
			used[i] = false;
		}
	}
	return;
}

int main () {
	cin>>n;
	for(int i = 1; i<=n; i++) {
		cin>>s[i];
		s[i+n] = s[i];
	}
	cin.get();
	st = cin.get();
	for(int i = 1; i<=2*n; i++) {
		if(s[i][0]==st) {
			used[i] = true;
			dfs(s[i], s[i].length());
			used[i] = false;
		}
	}
	cout<<Ans<<endl;
	return 0;
}

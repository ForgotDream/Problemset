#include <iostream>
#include <cstdio>
#include <vector>

typedef vector<bool> vec;

using namespace std;

int s[10][10];
bool row[10][10], column[10][10];
bool each[10][10];
bool solved[10];

void pr_int () {
	for(int i = 1; i<=9; i++) {
		for(int j = 1; j<=9; j++)
			cout<<s[i][j]<<' ';
		cout<<endl;
	}
}

void solve(int step = 1) {
	if(step==10) {
		pr_int();
		return;
	}
	for(int m = 1; m<=9; m++) {
		if(used[m]) continue;
		used[m] = true;
		for(int i = 1; i<=3; i++) {
			for(int j = 1; j<=3; j++) {
				if(!s[i][j]) continue;
				for(int k = 1; k<=9; k++)
					if(!each[i][k]&&!row[j+(m-1)/3*3][k]&&!column[i+(m-1)%3*3][k])
						s[i][j] = k, each[i][k] = true, row[j+(m-1)/3*3][k] = true, column[i+(m-1)%3*3][k] = true;
			}
		}
		dfs(step+1);
		//used[i] = false;
	}
	return;
}

int main () {
	for(int i = 1; i<=9; i++)
		for(int j = 1; j<=9; j++) {
			cin>>s[i][j];
			each[((j/3)+1)*((i/3)+1)][s[i][j]] = true;
			row[][s[i][j]] = true;
			column[s[i][j]] = true;
		}
	dfs();
	return 0;
}

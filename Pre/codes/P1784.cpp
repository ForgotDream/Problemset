#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>

using namespace std;

int a[10][10];
bool col[10][10], row[10][10], sq[100][10], ori[10][10];
struct d {
	int t, no;
} num[10];

bool cmp (d a, d b) {
	return a.t > b.t;
}

void pr_int () {
	for(int i = 1; i<=9; i++) {
		for(int j = 1; j<=9; j++)
			cout<<a[i][j]<<' ';
		cout<<endl;
	}
	//getchar();
	return;
}

void solve (int n, int x, int y) {
	if(n==10) {
		pr_int();
		//return;
		exit(0);
	}
	if(ori[x][y]) {
		if(y==9) solve(n+1, num[n+1].no, 1);
		else solve(n, x, y + 1);
	} else {
		int e = (x - 1) / 3 * 3 + (y - 1) / 3 + 1;
		for(int j = 1; j<=9; j++) {
			if(col[y][j]||row[x][j]||sq[e][j]) continue;
			a[x][y] = j;
			col[y][j] = true;
			row[x][j] = true;
			sq[e][j] = true;
			if(y==9) solve(n+1, num[n+1].no, 1);
			else solve(n, x, y + 1);
			col[y][j] = false;
			row[x][j] = false;
			sq[e][j] = false;
		}
	}
	return;
}

int main () {
	for(int i = 1; i<=9; i++)
		for(int j = 1; j<=9; j++) {
			int e = (i - 1) / 3 * 3 + (j - 1) / 3 + 1;
			cin>>a[i][j];
			num[i].no = i;
			if(a[i][j]!=0) num[i].t++, row[i][a[i][j]] = true, col[j][a[i][j]] = true, sq[e][a[i][j]] = true, ori[i][j] = true;
		}
	sort(num+1, num+10, cmp);
	solve(1, num[1].no, 1);
	return 0;
}

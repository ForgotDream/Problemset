#include <iostream>
#include <cstdio>

using namespace std;

int n;
int mat[35][35];
bool used[35][35], ans[35][35];
int d[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

void bfs (int sx, int sy) {
	int qx[2050], qy[2050];
	int head = 1, tail = 2;
	qx[head] = sx, qy[head] = sy;
    used[sx][sy] = true;
	bool flag = true;
	while(head<tail) {
		for(int i = 0; i<4; i++) {
			int dx = qx[head] + d[i][0], dy = qy[head] + d[i][1];
			if(mat[dx][dy]||used[dx][dy]) continue;
			if(dx<1||dx>n||dy<1||dy>n) {
				flag = false;
				continue;
			}
			used[dx][dy] = true;
			qx[tail] = dx, qy[tail] = dy;
			tail++;
		}
		head++;
	}
	if(!flag) {
		for(int i = 1; i<tail; i++) ans[qx[i]][qy[i]] = true;
	}
	return;
}

int main () {
	cin>>n;
	for(int i = 1; i<=n; i++) {
		for(int j = 1; j<=n; j++) {
			cin>>mat[i][j];
			if(mat[i][j]) ans[i][j] = true;
		}
	}
	for(int i = 1; i<=n; i++) {
		for(int j = 1; j<=n; j++) {
			if(!used[35][35]&&!mat[i][j]) bfs(i, j);
		}
	}
	for(int i = 1; i<=n; i++) {
		for(int j = 1; j<=n; j++) {
			if(ans[i][j]) cout<<mat[i][j]<<' ';
			else cout<<2<<' ';
		}
		cout<<endl;
	}
	return 0;
}

#include <iostream>
#include <cstdio>

using namespace std;

int mat[305][305];
int n, m;
char ch;
int sx, sy, ex, ey;
bool used[305][305];

void bfs () {
	int qx[90050], qy[90050];
	int head = 1, tail = 2;
	qx[head] = sx, qy[head] = sy;
	used[sx][sy] = false;
	while(head<tail) {
		if(mat[qx[head]][qy[head]]>='A')
	}
	return;
}

int main () {
	cin>>n>>m;
	for(int i = 1; i<=n; i++) {
		for(int j = 1; j<=m; j++) {
			cin>>ch;
			if(ch=='#') mat[i][j] = 1;
			else if(ch=='.') mat[i][j] = 0;
			else if(ch=='@') mat[i][j] = 0, sx = i, sy = j;
			else if(ch=='=') mat[i][j] = 0, ex = i, ey = j;
			else {
				mat[i][j] = ch;
			}
		}
	}
	bfs();
	return 0;
}

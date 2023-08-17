#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

int n, m;
bool mat[1050][1050];
bool used[1050][1050];
int d[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
int qx[1000050], qy[1000050];
int color[1050][1050];

int bfs (int sx, int sy) {
#define x_h qx[head]
#define y_h qy[head]
#define x_t qx[tail]
#define y_t qy[tail]
	memset(qx, 0, sizeof(qx));
	memset(qy, 0, sizeof(qy));
	int head = 1, tail = 2, ans = 1;
	x_h = sx, y_h = sy;
	used[sx][sy] = true;
	while(head<tail) {
		for(int i = 0; i<4; i++) {
			int dx = x_h + d[i][0], dy = y_h + d[i][1];
			if(dx<1||dx>n||dy<1||dy>n||used[dx][dy]) continue;
			if(mat[x_h][y_h]==mat[dx][dy]) continue;
			x_t = dx, y_t = dy;
			used[dx][dy] = true;
			//t[dx][dy] = t[x_h][y_h] + 1;
			ans++;
			tail++;
		}
		head++;
	}
	for(int i = 1; i<=tail; i++) {
		color[qx[i]][qy[i]] = ans;
	}
#undef x_h
#undef y_h
#undef x_t
#undef y_t
	return ans;
}

int main () {
    ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	freopen("P1141_2.in", "r", stdin);
	cin>>n>>m;
	for(int i = 1; i<=n; i++) {
		for(int j = 1; j<=n; j++) {
			char ch;
			cin>>ch;
			mat[i][j] = ch - '0';
		}
	}
	for(int i = 1; i<=n; i++) {
		for(int j = 1; j<=n; j++) {
			if(color[i][j]!=0) continue;
			else if(color[i][j]==0) bfs(i, j);
		}
	}
	while(m--) {
		int sx, sy;
		cin>>sx>>sy;
		cout<<color[sx][sy]<<endl;
	}
	return 0;
}

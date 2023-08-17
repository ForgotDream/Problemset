#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

int x1, y1, x2, y2;
bool used[25][25];
int d[12][2] = {{2, 1}, {2, -1}, {-2, 1}, {-2, -1}, {1, 2}, {1, -2}, {-1, 2}, {-1, -2}, {2, 2}, {2, -2}, {-2, 2}, {-2, -2}};
int t[25][25];

int bfs (int x, int y) {
	memset(used, 0, sizeof(used));
	memset(t, 0, sizeof(t));
	#define x_h qx[head]
	#define y_h qy[head]
	#define x_t qx[tail]
	#define y_t qy[tail]
	int qx[1000050], qy[1000050];
	int head = 1, tail = 2;
	x_h = x, y_h = y;
    //cout<<x_h<<' '<<y_h<<endl;
	used[x][y] = true;
	while(head<tail) {
		if(x_h==1&&y_h==1) {
			return t[x_h][y_h];
		}
		for(int i = 0; i<12; i++) {
			int dx = x_h + d[i][0], dy = y_h + d[i][1];
			if(dx<1||dx>20||dy<1||dy>20||used[dx][dy]) continue;
			x_t = dx, y_t = dy;
			used[dx][dy] = true;
			t[dx][dy] = t[x_h][y_h] + 1;
			tail++;
		}
		head++;
	}
	#undef x_h
	#undef y_h
	#undef x_t
	#undef y_t
	return -1;
}

int main () {
	cin>>x1>>y1>>x2>>y2;
	cout<<bfs(x1, y1)<<endl;
	cout<<bfs(x2, y2)<<endl;
	return 0;
}

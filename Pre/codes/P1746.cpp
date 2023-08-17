#include <iostream>
#include <cstdio>

using namespace std;

int n;
int t[1050][1050];
bool mat[1050][1050];
int sx, sy, ex, ey;
bool used[1050][1050];
int d[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

int bfs () {
	#define x_h qx[head]
	#define y_h qy[head]
	#define x_t qx[tail]
	#define y_t qy[tail]
	int qx[1000050], qy[1000050];
	int head = 1, tail = 2;
	x_h = sx, y_h = sy;
    //cout<<x_h<<' '<<y_h<<endl;
	used[sx][sy] = true;
	while(head<tail) {
		if(x_h==ex&&y_h==ey) {
			return t[x_h][y_h];
		}
		for(int i = 0; i<4; i++) {
			int dx = x_h + d[i][0], dy = y_h + d[i][1];
			if(dx<1||dx>n||dy<1||dy>n||used[dx][dy]||mat[dx][dy]) continue;
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
	cin>>n;
	for(int i = 1; i<=n; i++) {
		for(int j = 1; j<=n; j++) {
			char c;
			cin>>c;
			//cout<<c<<endl;
			mat[i][j] = c - '0';
		}
	}
    cin>>sx>>sy>>ex>>ey;
	cout<<bfs()<<endl;
	return 0;
}

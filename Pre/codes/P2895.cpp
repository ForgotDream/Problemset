#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

struct star{
	int t, x, y;
} l[50050];
int m;
bool used[305][305];
int t[305][305], at[305][305];
int d[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

int bfs () {
	int qx[90050], qy[90050];
	int head = 1, tail = 2;
	while(head<tail) {
		for(int i = 0; i<4; i++) {
			int dx = qx[head] + d[i][0], dy = qy[head] + d[i][1];
			t[dx][dy] = t[qx[head]][qy[head]] + 1;
			if(dx<0||dx>305||dy<0||dy>305||used[dx][dy]) continue;
			if(at[dx][dy]==0x3f3f3f3f) return t[dx][dy];
			if(at[dx][dy]<=t[dx][dy]) continue;
			used[dx][dy] = true;
			qx[tail] = dx, qy[tail] = dy;
			tail++; 
		}
		head++;
	}
	return -1;
}

int main () {
	cin>>m;
	memset(a,0x3f,sizeof(0x3f));
	for(int i = 1; i<=m; i++) {
		cin>>l[i].x>>l[i].y>>l[i].t;
		at[l[i].x][l[i].y] = min(at[l[i].x][l[i].y], l[i].t);
        for(int j = 0; j<4; j++) {
			int tx = l[i].x + d[j][0], ty = l[i].y + d[j][1];
			at[tx][ty] = min(at[tx][ty], l[i].t);
		}
	}
	auto f = [](const star& a, const star& b) { return a.t>b.t; };
	sort(l+1, l+m+1, f);
	cout<<bfs()<<endl;
	return 0;
}

#include <iostream>

using namespace std;

struct thing {
	int v, w, belong;
} l[65];
int n, m;
int f[65][32005];

int main () {
	cin>>n>>m;
	for(int i = 1; i<=m; i++) {
		cin>>l[i].v>>l[i].w>>l[i].belong;
	}
	f[1][0] = 0;
	for(int i = 1; i<=m; i++) {
		for(int j = n; j>=0; j--) {
			if(l[i].belong!=0) f[i][j] = f[i-1][j];
			if(j>=l[i].v) {
				if(f[i-1][j-l[i].v]+l[i].v*l[i].w>=f[i-1][j]) {
					f[i][j] = f[i-1][j-l[i].v]+l[i].v*l[i].w;
					int p = j-l[i].v;
					for(int k = 1; k<65; k++) {
						if(l[k].belong!=i);
						else {
							if(p>=l[k].v) {
								if(f[i-1][p-l[k].v]+l[k].v*l[k].w>=f[i-1][p]) {
									f[i][p] = f[i-1][p-l[k].v]+l[k].v*l[k].w;
									p-=l[k].v;
								} else {
									f[i][p] = f[i-1][p];
								}
							} else {
								f[i][p] = f[i-1][p];
							}
						}
					}
				} else {
					f[i][j] = f[i-1][j];
				}
			} else {
				f[i][j] = f[i-1][j];
			}
		}
	}
	for(int i = 1; i<=m; i++) {
		for(int j = 0; j<=n; j++) {
			cout<<f[i][j]<<' ';
		}
		cout<<endl;
	}
	cout<<f[m][n]<<endl;
	return 0;
}

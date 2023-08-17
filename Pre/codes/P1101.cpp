#include <iostream>
#include <cstdio>

using namespace std;

int d[8][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {-1, -1}, {-1, 1}};
int n;
int mat[105][105];
bool ans[105][105] = {false};
char ch[7] = {'y', 'i', 'z', 'h', 'o', 'n', 'g'};

void search_ (int curx, int cury) {
	for(int i = 0; i<8; i++) {
		int dx = curx + d[i][0], dy = cury + d[i][1];
		if(dx<1||dx>n||dy<1||dy>n||mat[dx][dy]!=(int)ch[1]) continue;
		//cout<<i<<endl;
        //cout<<dx<<" "<<dy<<endl;
		bool flag = true;
		for(int j = 2; j<7; j++) {
			dx+=d[i][0], dy+=d[i][1];
			if(mat[dx][dy]!=(int)ch[j]||dx<1||dx>n||dy<1||dy>n) {
				flag = false;
				break;
			}
			//cout<<dx<<' '<<dy<<' '<<flag<<endl;
		}
		//cout<<endl;
		if(flag) {
			//cout<<"flag"<<endl;
			for(int k = 0; k<7; k++) {
				ans[dx][dy] = true;
				dx-=d[i][0], dy-=d[i][1];
				//cout<<dx<<' '<<dy<<endl;
			}
            //cout<<endl;
		}
	}
	return;
}

int main () {
	cin>>n;
	for(int i = 1; i<=n; i++) {
		for(int j = 1; j<=n; j++) {
			char c;
			cin>>c;
			mat[i][j] = (int)c;
		}
	}
	for(int i = 1; i<=n; i++) {
		for(int j = 1; j<=n; j++) {
			if(mat[i][j]==(int)'y') {
				search_(i, j);
				//cout<<i<<' '<<j<<endl;
			}
		}
	}
	for(int i = 1; i<=n; i++) {
		for(int j = 1; j<=n; j++) {
			if(ans[i][j]) cout<<(char)mat[i][j];
			else cout<<'*';
			//cout<<mat[i][j]<<' ';
		}
		cout<<endl;
	}
	return 0;
}

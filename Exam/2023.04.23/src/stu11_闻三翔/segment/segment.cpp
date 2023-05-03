# include <cstdio>
# include <iostream>
# include <algorithm>
# include <cstring>
# include <cmath>
using namespace std;
const int N = 1e5 + 50, Inf = 0x3f3f3f3f;
const double eps = 1e-5;
int mark[5][2];
double ki[5], bi[5], ans = Inf;
int flag;
double cal(int id, int k)
{
	int cur = (k == 2) ? 3 : 1;
	double x = ((mark[id][1] - bi[k]) * ki[k] - mark[id][0]) / (ki[k] * ki[k] + 1);
	if(x >= mark[cur][0] && x <= mark[cur + 1][0]) {
		return fabs((ki[k] * mark[id][0] + bi[k] - mark[id][1]) / (sqrt(ki[k] * ki[k] + 1)));
	}
	else return Inf;
}
double Dis(int xi, int yi, int xj, int yj)
{
	return sqrt((xi - xj) * (xi - xj) + (yi - yj) * (yi - yj));
} 
int main()
{
	freopen("segment.in", "r", stdin);
	freopen("segment.out", "w", stdout);
	//ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0);
	for(int i = 1; i <= 4; i ++) {
		for(int j = 0; j <= 1; j ++) {
			cin >>mark[i][j];
		}
	}
	if(mark[1][0] > mark[2][0]) swap(mark[1], mark[2]);
	if(mark[3][0] > mark[4][0]) swap(mark[3], mark[4]);
	for(int i = 1; i <= 2; i ++) {
		for(int j = 3; j <= 4; j ++) {
			ans = min(ans, Dis(mark[i][0], mark[i][1], mark[j][0], mark[j][1]));
		}
	}
	
	if(mark[1][0] == mark[2][0]) {
		flag ++;
	}
	if(mark[3][0] == mark[4][0]) {
		flag ++;
	}
	if(flag) {
		if(flag == 2) {
			printf("%.4lf", min(ans, fabs(mark[1][0] - mark[3][0])));
			return 0;
		}
		else {
			if(mark[1][0] == mark[2][0]) {
				ki[2] = (mark[3][1] - mark[4][1]) / (mark[3][0] - mark[4][0]);
				bi[2] = mark[3][1] - ki[1] * mark[3][0];
				
				ans = min(ans, cal(1, 2));
				ans = min(ans, cal(2, 2));
			}
			else {
				ki[1] = (mark[1][1] - mark[2][1]) / (mark[1][0] - mark[2][0]);
				bi[1] = mark[1][1] - ki[1] * mark[1][0];
				
				ans = min(ans, cal(3, 1));
				ans = min(ans, cal(4, 1));
			}
			printf("%.4lf", ans);
			return 0;
		}
	}
	ki[1] = (mark[1][1] - mark[2][1]) / (mark[1][0] - mark[2][0]);
	bi[1] = mark[1][1] - ki[1] * mark[1][0];
	
	ki[2] = (mark[3][1] - mark[4][1]) / (mark[3][0] - mark[4][0]);
	bi[2] = mark[3][1] - ki[1] * mark[3][0];
	
	for(int i = 1; i <= 4; i ++) {
		ans = min(ans, cal(i, (i <= 2) ? 2 : 1));
	}
	printf("%.4lf", ans);
	return 0;
}

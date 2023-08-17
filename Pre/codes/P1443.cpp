#include <iostream>
#include <cstdio>
#include <cmath>

using namespace std;

int n;
long long time_ = 0;
double dis[20][20], ans = 1e9+7;
struct Node {
	double x, y;
} l[20];
bool used[20];

void pre () {
	for(int i = 0; i<=n; i++) {
		for(int j = 0; j<=n; j++) {
			dis[i][j] = sqrt(pow(l[i].x-l[j].x, 2) + pow(l[i].y-l[j].y, 2));
		}
	}
	return;
}

void dfs (int step = 1, double sum = 0, int last = 0) {
	time_++;
	if(step==n+1) {
		ans = min(ans, sum);
		return;
	}
	if(sum>=ans) return;
	if(time_>=(long long)6*1e7+7) return;
	for(int i = 1; i<=n; i++) {
		if(!used[i]) {
			used[i] = true;
			dfs(step+1, sum+dis[i][last], i);
			used[i] = false;
		}
	}
	return;
}

int main () {
	cin>>n;
	for(int i = 1; i<=n; i++) {
		cin>>l[i].x>>l[i].y;
	}
	pre();
	dfs();
	printf("%.2lf\n", ans);
	return 0;
}

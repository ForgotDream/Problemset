#include <iostream>
#include <cstdio>
#include <cmath>

using namespace std;

int n, s[15], b[15];
long long ans = (1<<40);

void dfs (long long sum1, long long sum2, int step = 1) {
	if(step>=n) {
		if(sum1==1&&sum2==0) return;
		ans = min(ans, abs(sum1-sum2));
		return;
	}
	dfs(sum1*s[step], sum2+b[step], step+1);
	dfs(sum1, sum2, step+1);
	return;
}

int main () {
	cin>>n;
	for(int i = 1; i<=n; i++) {
		cin>>s[i]>>b[i];
	}
	dfs(1, 0);
	cout<<ans<<endl;
	return 0;
}

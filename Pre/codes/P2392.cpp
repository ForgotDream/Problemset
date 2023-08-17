#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

int s[4], a[4][25];
int t[4];
bool used[4][25];
int ans;

void dfs (int i, int step = 1, int l = 0, int r = 0) {
	if(step==s[i]+1) {
		t[i] = min(t[i], max(l, r));
		return;
	}
	int n = a[i][step];
	dfs(i, step+1, l+n, r);
	dfs(i, step+1, l, r+n);
	return;
}

int main () {
	cin>>s[0]>>s[1]>>s[2]>>s[3];
	//memset(t, 0x3f, sizeof(t));
	for(int i = 0; i<4; i++) {
		for(int j = 1; j<=s[i]; j++) cin>>a[i][j];
		t[i] = 1e9+7;
		dfs(i);
		ans+=t[i];
	}
	cout<<ans<<endl;
	return 0;
}

#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

int n, w;
int a[20];
int f[1<<18], g[1<<18];

int main () {
	cin>>n>>w;
	for(int i = 1; i<=n; i++) cin>>a[i];
	memset(f, 63, sizeof(f));
	f[0] = 1;
	g[0] = w;
	for(int i = 0; i<(1<<n); i++) {
		for(int j = 1; j<=n; j++) {
			if(i & (1<<(j-1))) continue;
			if(g[i]>=a[j] && f[i | (1<<(j-1))]>=f[i]) {
				f[i | (1<<(j-1))] = f[i];
				g[i | (1<<(j-1))] = max(g[i | (1<<(j-1))], g[i] - a[j]);
			} else if(g[i]<a[j] && f[i | (1<<(j-1))]>=f[i]+1) {
				f[i | (1<<(j-1))] = f[i] + 1;
				g[i | (1<<(j-1))] = max(g[i | (1<<(j-1))], w - a[j]);
			}
		}
	}
	cout<<f[(1<<n)-1]<<endl;
	return 0;
}

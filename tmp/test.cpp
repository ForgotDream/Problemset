#include<bits/stdc++.h>
using namespace std;
const int N=100,M=1024;
int n,m,ans,g[N],cnt[M];
int f[2][M][M]; vector<int> S;

char gc() {
    char ch=0; 
		while (!isalpha(ch) )
    	ch=getchar(); 
		return ch;
}
bool check(int x) {
    return !(x&x>>1||x&x>>2);
}
int count(int x) {
    int cnt=0; 
		while (x)
    	cnt++,x&=(x-1); 
		return cnt;
}
int main()
{
    scanf("%d%d",&n,&m);
    for (int i=0;i<n;i++) for (int j=0;j<m;j++) {
			g[i] = (g[i] << 1) + (gc() == 'H');
		}
    for (int i=0;i<1<<m;i++) if (check(i) ) S.push_back(i),cnt[i]=count(i);

    for (int i=0;i<n;i++)
        for (int x:S) for (int y:S) for (int z:S)
            if ( !(x&y) && !(x&z) && !(y&z) && !(g[i]&x) )
                f[i&1][x][y]=max(f[i&1][x][y],f[(i-1)&1][y][z]+cnt[x]);
    for (int u:S) for (int v:S) if (!(u&v) ) ans=max(ans,f[(n-1)&1][u][v]);
    printf("%d",ans); return 0;
}
#include <bits/stdc++.h>
using namespace std;
#define int __int128
inline int read(){
    int x=0;bool f=1;char c=getchar();
    while(c<48||c>57){if(c=='-') f=0;c=getchar();}
    while(c>=48&&c<=57){x=x*10+(c^48);c=getchar();}
    return f?x:-x;
}
inline void write(int x){
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10+48);
}
#define lcm(x,y) (x)*(y)/gcd((x),(y))
inline int gcd(int a,int b){
    if (b==0) return a;
    return gcd(b,a%b);
}
inline void simp(int &a, int &b) {
	int g = gcd(a, b);
	a /= g, b /= g;
}
inline pair<int,int> fs_equal(int a,int b,int c){
    if (a==0&&b==0) return make_pair(0,0);
    simp(a, b), simp(a, c);
		b *= c;
    simp(a, b);
    return make_pair(a,b);
}
inline void fs_clac(int &a,int &b,int c,int d){
    if (a==0&&b==0) {a=c,b=d;return;}
		simp(a, b), simp(c, d);
    a=a*d+b*c,b=b*d;
    simp(a, b);
}
int n,m,k,x,cnt,fs[200005][2],rd[200005];
vector<int>e[200005];
bool tmp[200005];
signed main(){
    n=read(),m=read();
    for (int i=1;i<=n;i++){
        k=read();
        if (k==0) tmp[i]=1;
        while (k--) x=read(),e[i].push_back(x),rd[x]++;
    }
    for (int i=1;i<=m;i++) fs[i][0]=1,fs[i][1]=1;
		std::queue<int> q;
    for (int i = 1; i <= m; i++) q.push(i);
		while (!q.empty()) {
			int u = q.front();
			q.pop();
			auto [up, dwn] = fs_equal(fs[u][0], fs[u][1], e[u].size());
			for (auto v : e[u]) {
				fs_clac(fs[v][0], fs[v][1], up, dwn);
				if (!--rd[v]) q.push(v);
			}
		}
    for (int i=1;i<=n;i++) if (tmp[i]) write(fs[i][0]),putchar(' '),write(fs[i][1]),putchar('\n');
    return 0;
}
/*
10 1
5 2 3 4 5 6
2 7 8
2 8 10
2 9 7
1 9
3 7 8 9
1 10
0
1 10
0

*/
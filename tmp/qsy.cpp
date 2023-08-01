#include<bits/stdc++.h>
#define ld long double
#define ui unsigned int
#define ull unsigned long long
#define int long long
#define eb emplace_back
#define pb pop_back
#define ins insert
#define mp make_pair
#define pii pair<int,int>
#define fi first
#define se second
#define power(x) ((x)*(x))
#define gcd(x,y) (__gcd((x),(y)))
#define lcm(x,y) ((x)*(y)/gcd((x),(y)))
#define lg(x,y)  (__lg((x),(y)))
#define y1 LJBL
using namespace std;
 
namespace FastIO
{
    template<typename T=int> inline T read()
    {
        T s=0,w=1; char c=getchar();
        while(!isdigit(c)) {if(c=='-') w=-1; c=getchar();}
        while(isdigit(c)) s=(s*10)+(c^48),c=getchar();
        return s*w;
    }
    template<typename T> inline void read(T &s)
    {
        s=0; int w=1; char c=getchar();
        while(!isdigit(c)) {if(c=='-') w=-1; c=getchar();}
        while(isdigit(c)) s=(s*10)+(c^48),c=getchar();
        s=s*w;
    }
    template<typename T,typename... Args> inline void read(T &x,Args &...args)
    {
        read(x),read(args...);
    }
    template<typename T> inline void write(T x,char ch)
    {
        if(x<0) x=-x,putchar('-');
        static char stk[25]; int top=0;
        do {stk[top++]=x%10+'0',x/=10;} while(x);
        while(top) putchar(stk[--top]);
        if(ch!='~') putchar(ch);
        return;
    }
}
using namespace FastIO;
 
inline void file()
{
    freopen(".in","r",stdin);
    freopen(".out","w",stdout);
    return;
}
 
bool Mbe;
 
namespace LgxTpre
{
    static const int MAX=200050;
    static const int inf=2147483647;
    static const int INF=4557430888798830399;
    static const int mod=1e9+7;
    static const int bas=131;
    
    int T,n,lstans,ans,x,y;
	int dis[MAX],vis[MAX],c[MAX],V[MAX],st;
    queue<int> q;
    
    struct edge{int nex,to;}e[MAX<<1];
    int head[MAX],cnt;
    inline void add(int x,int y) {e[++cnt].nex=head[x],head[x]=cnt,e[cnt].to=y;}

    inline void mian()
    {
    	auto bfs=[&](int S,int nowcol)
    	{
    		while(!q.empty()) q.pop();
    		q.push(S),vis[S]=1,dis[S]=1,V[S]=nowcol;
    		while(!q.empty())
    		{
    			int now=q.front(); q.pop();
    			for(int i=head[now];i;i=e[i].nex)
    			{
    				int to=e[i].to;
    				if(vis[to]&&to!=S) {ans=dis[now]; break;}
    				if(V[to]!=nowcol) q.push(to),dis[to]=dis[now]+1,V[to]=nowcol;
				}
				if(ans) break;
			}
		};
		
		read(T);
    	while(T--)
    	{
    		read(n,st),lstans=INF,cnt=0;
    		for(int i=1;i<=n;++i) head[i]=0,vis[i]=0,i<n?read(c[i]):void(),V[i]=0;
    		vis[st]=1;
    		for(int i=1;i<n;++i)  read(x,y),add(x,y),add(y,x);
    		for(int i=1;i<n;++i)  ans=0,bfs(c[i],i),lstans=min(lstans,ans),write(lstans,' ');
    		puts("");
		}
    	return;
    }
}

bool Med;

signed main()
{
//  file();
    fprintf(stderr,"%.3lf MB\n",abs(&Med-&Mbe)/1048576.0);
    int Tbe=clock();
    LgxTpre::mian();
    int Ted=clock();
    cerr<<1e3*(Ted-Tbe)/CLOCKS_PER_SEC<<" ms\n";
    return (0-0);
}

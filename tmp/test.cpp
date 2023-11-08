const int N=1e6+5;
int n,m,a[N],lst[N];
struct node{int pos,x;} t[N];
il bool cmp(node x,node y) {return x.pos<y.pos;}
struct que{int l,r,id;};
vector<que> q[N]; 
struct BIT
{
    int tr[N];
    il void modify(int x,int k) {for(;x<=n;x+=x&(-x)) tr[x]+=k;}
    il void add(int l,int r,int k) {modify(l,k),modify(r+1,-k);}
    il int query(int x) {int res=0;for(;x;x-=x&(-x)) res+=tr[x];return res%10;}
}tr[15];
int ans[N][15],vis[N];
int main()
{
    n=read(),m=read();
    for(int i=1;i<=n;i++) a[i]=read();
    for(int i=1;i<=m;i++)
    {
        int l=read(),r=read();
        q[r].push_back({l,r,i});
    }
    for(int i=1,mx=1e6;i<=n;i++)
    {
        int tot=1,L=a[i],R=a[i]; t[1]={i,a[i]}; 
        for(int j=max(1,a[i]-11);j<=min(mx,a[i]+11);j++)
        {
            vis[j]=0;
            if(lst[j]) t[++tot]={lst[j],j};
        }
        sort(t+1,t+tot+1,cmp);
        for(int j=tot;j&&t[j].pos>lst[a[i]];j--)
        {
            vis[t[j].x]=1;
            while(vis[L-1]&&L-1>=max(1,a[i]-11)) L--;
            while(vis[R+1]&&R+1<=min(mx,a[i]+11)) R++;
            tr[a[i]-L].add(t[j-1].pos+1,t[j].pos,-1);
            tr[R-a[i]].add(t[j-1].pos+1,t[j].pos,-1);
            if(R-L+1<=10) tr[R-L+1].add(t[j-1].pos+1,t[j].pos,1);
        }
        lst[a[i]]=i;
        for(auto x:q[i]) for(int j=1;j<=10;j++) ans[x.id][j]=tr[j].query(x.l);
    }
    for(int i=1;i<=m;i++,printf("\n")) 
        for(int j=1;j<=10;j++) printf("%d",ans[i][j]);
    return 0;
}

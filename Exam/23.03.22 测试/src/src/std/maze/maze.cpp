#include <cstdio>
#include <cstring>
using namespace std;
struct dd{ int x,y,z;};
int n,r,head[5001],tail[5001],dis[5001],s1,s2,ans=1000000000;
dd a[200001];
bool b[5001];
void qsort(int l1,int r1)
{
     if (l1>=r1) return;
     int i=l1,j=r1,t=(i+j)/2;
     dd k=a[t]; a[t]=a[i];
     while (i<j)
     {
         while (a[j].x>=k.x&&i<j) --j;
         if (i<j)
         {
             a[i]=a[j];
             ++i;
         }
         while (a[i].x<k.x&&i<j) ++i;
         if (i<j)
         {
             a[j]=a[i];
             --j;
         }
     }
     a[i]=k;
     qsort(l1,i-1); qsort(i+1,r1);
     return; 
}
void dfs(int k,int s3)
{
     if (s3>s1||s3>=ans) return;
     if (k==n&&s3>s2&&ans>s3)
     {
         ans=s3;
         return;
     }
     for (int i=head[k]; i<=tail[k]; ++i)
         dfs(a[i].y,s3+a[i].z);
     return;
}
int main()
{
    freopen("maze.in","r",stdin);
    freopen("maze.out","w",stdout);
    scanf("%d%d",&n,&r);
    for (int i=1; i<=r; ++i)
    {
        scanf("%d%d%d",&a[2*i-1].x,&a[2*i-1].y,&a[2*i-1].z);
        a[2*i].x=a[2*i-1].y; a[2*i].y=a[2*i-1].x;
        a[2*i].z=a[2*i-1].z;
    }
    r*=2;
    qsort(1,r);
    memset(head,0,sizeof(head));
    memset(tail,0,sizeof(tail));
    head[1]=1; tail[n]=r;
    for (int i=1; i<=r; ++i)
    {
        if (i>1&&a[i].x!=a[i-1].x)
            head[a[i].x]=i;
        if (i<r&&a[i].x!=a[i+1].x)
            tail[a[i].x]=i;
    }
    for (int i=1; i<=n; ++i)
        dis[i]=1000000000;
    dis[1]=0;
    memset(b,false,sizeof(b));
    for (int i=1; i<=n; ++i)
    {
        int minn=1000000000,k=0;
        for (int j=1; j<=n; ++j)
            if (dis[j]<minn&&!b[j])
            {
                minn=dis[j]; 
                k=j;
            }
        b[k]=true;
        for (int j=head[k]; j<=tail[k]; ++j)
            if (dis[a[j].y]>dis[k]+a[j].z)
            {
                dis[a[j].y]=dis[k]+a[j].z;
                if (a[j].y==n) s1=a[j].z*2;
            }
    }
    s2=dis[n]; s1+=s2;
    dfs(1,0);
    printf("%d",ans);
    return 0;
}
    

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
using namespace std;

long n,m,k1,k2,ans=2147483647;
const long dx[4]={0,-1,0,1};
const long dy[4]={-1,0,1,0};


long map[51][51];
long ans_map[51][51];
long g[10001][3];

void init()
{
	freopen("matrix.in","r",stdin);
    scanf("%d%d%d%d",&n,&m,&k1,&k2);
    fclose(stdin);
}

bool check_out(long a,long b)
{
    if (a<1 || a>n || b<1 || b>m) return false;
    if (map[a][b]==0 && map[a-1][b]!=0 && map[a+1][b]!=0 && map[a][b-1]!=0 && map[a][b+1]!=0) return true;
    return false;
}
    


void sub(long a,long b,long l,long best)
{
    if (l>m*n) 
    {
        ans=best;//printf("%d\n",ans);
        memcpy(ans_map,map,sizeof map);
    }
    else
    {
        if (check_out(a+1,b+1) || check_out(a-1,b-1) || check_out(a+1,b-1) || check_out(a-1,b+1)) return;
        long i,j,k,tem;
        
        for (k=0;k<4;k++)
        {
            i=a+dy[k];
            j=b+dx[k];
            if (i>=1 && i<=n && j>=1 && j<=m && map[i][j]!=0 && map[a+dy[(k+2)%4]][b+dx[(k+2)%4]]!=0 && 
                map[a+dy[(k+3)%4]][b+dx[(k+3)%4]]==0 && map[a+dy[(k+1)%4]][b+dx[(k+1)%4]]==0) return;
        } 
        for (k=0;k<4;k++)
        {
            i=a+dy[k];
            j=b+dx[k];

            if (i>=1 && i<=n && j>=1 && j<=m && map[i][j]==0)
            {
                
                if (l*2<=m*n)
                {
                    g[l][1]=i;g[l][2]=j;tem=best;
                }
                else
                {
                    tem=k1*abs(i-g[l-m*n/2][1])+k2*abs(j-g[l-m*n/2][2]);
                    if (tem>=ans) continue;
                    if (tem<best) tem=best;
                }
                
                map[i][j]=(l-1)%(n*m/2)+1;
                sub(i,j,l+1,tem);
                map[i][j]=0;
            }
            
        }
    }
}
        
    

int main()
{
    init();
    
    long i,j,l,r,min;
    l=0;r=k1*(n-1)+k2*(m-1);
        
    memset(map,-1,sizeof map);
    for (i=1;i<=n;i++) for (j=1;j<=m;j++) map[i][j]=0;
    map[1][1]=1;g[1][1]=1;g[1][2]=1;
    
    
    sub(1,1,2,0);
    freopen("matrix.out","w",stdout);
    printf("%d\n",ans);
    fclose(stdout);
/*    for (i=1;i<=n;i++)
    {
        for (j=1;j<=m;j++) printf("%5d",ans_map[i][j]);
        printf("\n");
    }
*/
}

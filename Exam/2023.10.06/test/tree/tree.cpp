# include <cstdio>
# include <algorithm>
# include <cstring>
# include <set>
# define ll long long
using namespace std;
int Read()
{
    int f=1;//����������� 
	int x=0;//��¼��������� 
    char c;
    while( (c=getchar() )<'0'||c>'9')//��ȡ'-' 
        if(c=='-')  f=-1;
    x=c-'0';//�ϸ�ѭ����ȡ�����־�ͣ�� 
    while( (c=getchar() )>='0'&& c<='9')
        x=x*10+c-'0';
    x*=f;
    return x;
}

int T,n,m,l,r,pre[100005],ans[100005];
int main()
{
    freopen("tree.in", "r", stdin);
    freopen("tree.out", "w", stdout);
    T=Read();
    while(T--){
        memset(pre,0,sizeof(pre));
        n=Read(); m=Read();
        for(int i=1;i<=n;i++)
            pre[i]=i;
        for(int i=0;i<m;i++){
            l=Read(); r=Read();
            pre[r]=min(pre[r],l);
        }

        for(int i=n-1;i>=1;i--)
            pre[i]=min(pre[i],pre[i+1]);
        int pl=1;
        set<int>s;
        for(int i=1;i<=n;i++)
            s.insert(i);
        for(int i=1;i<=n;i++){
            while(pl<pre[i]){
                s.insert(ans[pl]);
                pl++;
            }
            ans[i]=*s.begin();
            s.erase(ans[i]);
        }

       printf("%d",ans[1]);
       for(int i=2;i<=n;i++)
            printf(" %d",ans[i]);
       printf("\n"); 
    }
    return 0;
}

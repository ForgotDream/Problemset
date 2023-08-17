//模拟加贪心，类似于均分纸牌，注意处理位置之间的相对关系 
# include <cstdio>
# include <cstring>
# include <algorithm>
# define N 100010
using namespace std;
int n, a[N], b[N];
long long ans; 
int main()
{
	freopen("queue.in", "r", stdin);
	freopen("queue.out", "w", stdout);
	scanf("%d", &n);
	for (int i=1; i<=n; i++)
	    scanf("%d", &a[i]);
	
	sort(a+1, a+n+1);	
	for (int i=n; i>=1; i--)  a[i]-=a[1];//处理相对位置关系，参照位置调整为0 
	
	memcpy(b,a,sizeof(b));//备份数组，b为镜像数组 
	for (int j=0; j<5; j++)//其实j取0,3,4枚举就可以了，测试数据好像取0模拟一遍就对 
	{
		long long _now = 0;
		memcpy(a,b,sizeof(b));
		for (int i=1; i<=n; i++)   a[i]+=j;
	    
		for (int i=1; i<=n; i++)//贪心：总是先执行跨步大的命令 
	    {
	     	if(a[i]>=5) _now+=(long long)a[i]/5, a[i] %= 5;//当前这个人-5就相当于其他人+5 
		    if (a[i]>=2) _now+=(long long)a[i]/2, a[i] %= 2;//当前这个人-2就相当于其他人+2 
		    if (a[i]>0) _now+=(long long)a[i], a[i] = 0;//当前这个人-1就相当于其他人+1 
	    }	    
		if(j==0 ) ans=_now;  else ans=min(ans,_now);//min函数在algorithm头文件中，两个数据的类型要一致 
    }
	printf("%lld", ans);
	return 0;
}

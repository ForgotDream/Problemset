//ģ���̰�ģ������ھ���ֽ�ƣ�ע�⴦��λ��֮�����Թ�ϵ 
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
	for (int i=n; i>=1; i--)  a[i]-=a[1];//�������λ�ù�ϵ������λ�õ���Ϊ0 
	
	memcpy(b,a,sizeof(b));//�������飬bΪ�������� 
	for (int j=0; j<5; j++)//��ʵjȡ0,3,4ö�پͿ����ˣ��������ݺ���ȡ0ģ��һ��Ͷ� 
	{
		long long _now = 0;
		memcpy(a,b,sizeof(b));
		for (int i=1; i<=n; i++)   a[i]+=j;
	    
		for (int i=1; i<=n; i++)//̰�ģ�������ִ�п粽������� 
	    {
	     	if(a[i]>=5) _now+=(long long)a[i]/5, a[i] %= 5;//��ǰ�����-5���൱��������+5 
		    if (a[i]>=2) _now+=(long long)a[i]/2, a[i] %= 2;//��ǰ�����-2���൱��������+2 
		    if (a[i]>0) _now+=(long long)a[i], a[i] = 0;//��ǰ�����-1���൱��������+1 
	    }	    
		if(j==0 ) ans=_now;  else ans=min(ans,_now);//min������algorithmͷ�ļ��У��������ݵ�����Ҫһ�� 
    }
	printf("%lld", ans);
	return 0;
}

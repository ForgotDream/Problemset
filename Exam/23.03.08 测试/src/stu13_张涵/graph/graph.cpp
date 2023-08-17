#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<cmath>
#include<unordered_map>
#include<bitset>
using namespace std;
int n,m;
struct EDGE
{
	int from,to,w,Next;
}edge[200005];
int total,head[100005];
inline void add_edge(int u,int v,int w)
{
	edge[++total]=EDGE{u,v,w,head[u]};head[u]=total;
}
int point[100005];
int color[100005];
double ans;
int main()
{
	freopen("graph.in","r",stdin);
	freopen("graph.out","w",stdout);
	scanf("%d %d",&n,&m);
	int sump=0,sume=0;
	for (int i=1;i<=n;i++)
		scanf("%d",&point[i]),sump+=point[i];
	for (int i=1,u,v,w;i<=m;i++)
	{
		scanf("%d %d %d",&u,&v,&w);
		add_edge(u,v,w);
		add_edge(v,u,w);
		sume+=w;
		ans=max(ans,(point[u]+point[v])*1.0/w);
	}
	if (m==0)
	{
		printf("0");
		return 0;
	}
	if (n==2)
	{
		double temp=(sump*1.0)/sume;
		printf("%.2lf",temp);
		return 0;
	}
	printf("%.2lf",ans);
	return 0;
}
/*
ѡһ���㣬ɾ������������������������б�
�ظ��˲���

������ͼֻ��һ��SCC(����������) ʱ���Խ���

ʹ��������ͼ �ĵ�Ȩ�ͱȱ�Ȩ�����  
*/

#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<set>
#include<queue>
#include<stack>
#include<cmath>
using namespace std;
#define ldouble long double
#define eps 1e-6
struct Node
{
	int From[2];//芍????迄℅車 
	int Out,OutSign;//那?3? 
	int tot;//?迄℅車??那y 
	int sign[2];//2???迄℅車米?D?o? 
	int type;
}tree[400000];
int dp[400000][2];
int N,M;
int root;
//dp[pos][0] ????∩|那?3????a0?迄D豕米?℅?D?﹞?車?㏒?dp[pos][1] ??3谷1 
int getVal(int pos)
{
	for(int i=0,Next;i<tree[pos].tot;i++)
	{
		Next=tree[pos].From[i];
		tree[pos].sign[i]=getVal(Next);
	}
	if(tree[pos].tot==0)
	{
		tree[pos].OutSign=tree[pos].sign[0];	
		return tree[pos].sign[0];	
	}
	if (tree[pos].type==1)
	{
		tree[pos].OutSign=tree[pos].sign[0]&tree[pos].sign[1];	
	}
	else if (tree[pos].type==2)
	{
		tree[pos].OutSign=tree[pos].sign[0]|tree[pos].sign[1];
	}
 	else if(tree[pos].type==3)
	{
		tree[pos].OutSign=tree[pos].sign[0]^tree[pos].sign[1];
	}
	return tree[pos].OutSign;
}
void dfs(int pos)
{
	for(int i=0,Next;i<tree[pos].tot;i++)
	{
		Next=tree[pos].From[i];
		dfs(Next);
	}
	if (tree[pos].tot==0)
	{
		dp[pos][tree[pos].sign[0]]=0;
		dp[pos][!tree[pos].sign[0]]=1;
		return ;
	}
	dp[pos][tree[pos].OutSign]=0;
	if (tree[pos].type==1)// &
	{
		if (tree[pos].OutSign==1)
			dp[pos][0]=min(dp[tree[pos].From[0]][0]+dp[tree[pos].From[1]][0],
					       min(dp[tree[pos].From[0]][1]+dp[tree[pos].From[1]][0],
						   	   dp[tree[pos].From[0]][0]+dp[tree[pos].From[1]][1])
			);
		else 
			dp[pos][1]=dp[tree[pos].From[0]][1]+dp[tree[pos].From[1]][1];
	}
	else if(tree[pos].type==2)// |
	{
		if (tree[pos].OutSign==0)
			dp[pos][1]=min(dp[tree[pos].From[0]][1]+dp[tree[pos].From[1]][1],
					       min(dp[tree[pos].From[0]][1]+dp[tree[pos].From[1]][0],
						   	   dp[tree[pos].From[0]][0]+dp[tree[pos].From[1]][1])
			);
		else 
			dp[pos][0]=dp[tree[pos].From[0]][0]+dp[tree[pos].From[1]][0];
	}
	else if (tree[pos].type==3)// ^
	{
		if (tree[pos].OutSign==0)
			dp[pos][1]=min(dp[tree[pos].From[0]][1]+dp[tree[pos].From[1]][0],
						   dp[tree[pos].From[0]][0]+dp[tree[pos].From[1]][1]);
		else 
			dp[pos][0]=min(dp[tree[pos].From[0]][0]+dp[tree[pos].From[1]][0],
						   dp[tree[pos].From[0]][1]+dp[tree[pos].From[1]][1]);
	}
}
inline void debug(int pos)
{
	printf("%d %d %d\n",pos,dp[pos][0],dp[pos][1]);
}
inline void getson(int pos)
{
	cerr<<tree[pos].From[0]<<' '<<tree[pos].From[1]<<'\n';
}
inline void print(int pos)
{
	printf("\n");
	printf("Node %d\n",pos);
	printf("type %d\n",tree[pos].type);
	printf("From %d %d \n",tree[pos].From[0],tree[pos].From[1]);
	printf("sign %d %d \n",tree[pos].sign[0],tree[pos].sign[1]);
	printf("DP %d %d\n",dp[pos][0],dp[pos][1]);
	printf("\n");
}
int main()
{
	freopen("logical.in","r",stdin);
	freopen("logical.out","w",stdout);
	scanf("%d %d",&N,&M);
	for (int i=1;i<=N;i++)
	{
		scanf("%d %d %d %d",&tree[i].From[0],&tree[i].From[1]
						   ,&tree[i].Out,&tree[i].type); 
		if (tree[i].From[0]&&tree[i].From[1]) tree[i].tot=2;
		else if (tree[i].From[0]||tree[i].From[1])
		{
			tree[i].From[0]=max(tree[i].From[0],tree[i].From[1]);
			tree[i].tot=0;
		}
		else tree[i].tot=0;
		if (tree[i].Out==0) root=i;
	}
	for(int i=1,id;i<=M;i++)
	{
		scanf("%d",&id);
		scanf("%d",&tree[id].sign[0]);
	}
	int Val=getVal(root);
	dfs(root);	
/*	debug(1);
	debug(2);
	debug(15);
	debug(19);
	debug(27);
	debug(29);
	debug(31);
	getson(31);
	debug(32);debug(35);
	print(31);
	print(32);
	print(35);*/
	/*for (int i=1;i<=N;i++)
	{
		printf("%d %d %d\n",i,dp[i][0],dp[i][1]);
	}*/
	/*cerr<<"Val "<<Val<<endl;
	cerr<<dp[root][Val]<<endl;
	cerr<<dp[root][!Val]<<endl;*/
	printf("%d",dp[root][!Val]);
	return 0;
}

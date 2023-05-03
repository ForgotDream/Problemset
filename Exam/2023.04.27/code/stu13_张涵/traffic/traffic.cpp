#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
struct EDGE
{
	int to,Next,w;
}edge[500000*2+5];
int head[250000+5],total;
int dis[250000*2+5];
//dis[i] μ?i?·?ú?ìμ?μ?×??ìê±?? dis[i+n] μ? i ?·?ú?ìμ?μ?×??ìê±?? 
bool inq[250000*2+5];
inline void add_edge(int u,int v,int w)
{
	edge[++total]=EDGE{v,head[u],w};
	head[u]=total;
}
int R[250000*2+5],G[250000*2+5];
int n,m;
inline bool check_GorR(int Time,int pos)
{
	int res=Time%(R[pos]+G[pos]);
	if (1<=res&&res<=R[pos])
		return false;//oìμ?
	return true;//?ìμ? 
}
inline int GetTime_GtoR(int Time,int pos)
{
	if (Time%(R[pos]+G[pos]))
		return (R[pos]+G[pos])*(Time/(R[pos]+G[pos])+1);
	return Time+1;
}
inline int GetTime_RtoG(int Time,int pos)
{
	return Time+R[pos]-Time%(R[pos]+G[pos]);
}
deque<int>dq;
inline void push(int pos)
{
	if (!dq.empty())
	{
		if (dis[pos]<=dis[dq.front()])
			dq.push_front(pos);
		else dq.push_back(pos);
		if (dis[dq.back()]<dis[dq.front()])
			swap(dq.front(),dq.back());
	}
	else dq.push_front(pos);
}
inline void pop()
{
	dq.pop_front();
	if (!dq.empty()&&dis[dq.back()]<dis[dq.front()])
		swap(dq.front(),dq.back());
}
inline void spfa(int s)
{
	//这里有个Dij不会写的憨批 
	memset(dis,0x3f,sizeof(dis));
	//queue<int>q;
	inq[s]=true;
	inq[s+n]=true;
	dis[s]=R[s];
	dis[s+n]=0;
	push(s),push(s+n);
	/*q.push(s);
	q.push(s+n);*/
	int pos,res;
	int resNextR,resNextG;
	while (!dq.empty())
	{
		//pos=q.front();
		pos=dq.front();pop();
		inq[pos]=false;
		//q.pop();
		if (pos>n) res=R[pos]-dis[pos]%(R[pos]+G[pos])+1;//±??ìμ?òaμ?ê±?? 
		else res=0;
		int BB=pos>n?pos-n:pos;
		for (int e=head[BB],Next,Time;e;e=edge[e].Next)
		{
			Next=edge[e].to;
			Time=edge[e].w+dis[pos]+res;
			if (check_GorR(Time+1,Next))//?ìμ? 
			{
				 if (dis[Next]>Time)
				 {
				 	dis[Next]=Time;
				 	if (!inq[Next])
				 		//q.push(Next),inq[Next]=true;
				 		push(Next),inq[Next]=true;
				 }
				 if (dis[Next+n]>GetTime_GtoR(Time,Next)) 
				 {
				 	dis[Next+n]=GetTime_GtoR(Time,Next);
				 	if (!inq[Next+n])
				 		//q.push(Next+n),inq[Next+n]=true;
				 		push(Next+n),inq[Next+n]=true;
				 }
			}
			else //oìμ? 
			{
				if (dis[Next]>GetTime_RtoG(Time,Next))
				{
					dis[Next]=GetTime_RtoG(Time,Next);
					if (!inq[Next])
				 		//q.push(Next),inq[Next]=true;
				 		push(Next),inq[Next]=true;
				}
				if (dis[Next+n]>Time)
				{
					dis[Next+n]=Time;
					if (!inq[Next+n])
						//q.push(Next+n),inq[Next+n]=true;
						push(Next+n),inq[Next+n]=true;
				}
			}
		}
	}
}
int A,B;
int main()
{
	freopen("traffic.in","r",stdin);
	freopen("traffic.out","w",stdout);
	scanf("%d %d %d %d",&n,&m,&A,&B);
	for (int i=1;i<=n;i++)
		scanf("%d %d",&R[i],&G[i]),R[i+n]=R[i],G[i+n]=G[i];
	for (int i=1,x,y,w;i<=m;i++)
	{
		scanf("%d %d %d",&x,&y,&w);
		add_edge(x,y,w);add_edge(y,x,w);
	}
	spfa(A);
	printf("%d\n",min(dis[B],dis[B+n]));
	/*for (int i=1;i<=n;i++)
		printf("%d %d\n",dis[i+n],dis[i]);*/
	return 0;
}

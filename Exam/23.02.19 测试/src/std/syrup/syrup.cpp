#include <cstdio>
#include <cstring>

using std::printf;
using std::scanf;
using std::memset;

const long OO=1000000;
const long maxn=2000;
long N;
long G[maxn][maxn];//G[x][y]表示x和y能配制的药水编号
bool fixed[maxn];
long cost[maxn];
long long way[maxn];
template <class T>
int update(T& old, const T& updater){
	if(old>updater){
		old=updater;
		return 1;
	}
	if(old==updater)return 0;
	return -1;
}
inline void input(){
	freopen("syrup.in","r",stdin);
	scanf("%d",&N);//cin>>N;
	for(long i=0;i<N;++i)scanf("%d",&cost[i]);//cin>>cost[i];
	memset(G,-1,sizeof(G));
	while(true){
		long A,B,C;
		if(scanf("%d%d%d",&A,&B,&C)==EOF)break;//if(!(cin>>A>>B>>C))break;
		G[A][B]=G[B][A]=C;
	}
	memset(fixed,false,sizeof(fixed));
	for(long i=0;i<maxn;++i)way[i]=1LL;
	fclose(stdin);
}
inline void solve(){
	while(true){
		long MinCost=OO;
		long MinI=-1;
		for(long i=0;i<N;++i){
			if(fixed[i])continue;
			if(cost[i]<MinCost){
				MinCost=cost[i];
				MinI=i;
			}
		}
		fixed[MinI]=true;
		if(MinI==0)break;
		for(long i=0;i<N;++i){
			if(!fixed[i])continue;
			if(G[MinI][i]!=-1){
				switch(update(cost[G[MinI][i]],cost[MinI]+cost[i])){
					case 1:
						way[G[MinI][i]]=way[MinI]*way[i];
						break;
					case 0:
						way[G[MinI][i]]+=way[MinI]*way[i];
				}
			}
		}
	}
}
inline void output(){
	freopen("syrup.out","w",stdout);
	printf("%d %d\n",cost[0],way[0]);//cout<<cost[0]<<' '<<way[0]<<endl;
	fclose(stdout);
}
int main(){
	input();
	solve();
	output();
}

#include<cstdio>
#include <deque>
#include<iostream>
#include<cstring>
#include<algorithm>
#include <memory>
#include<queue>
#include<cmath>
#include <utility>
using namespace std;
int Sx,Sy,Ex,Ey;
int Deltax,Deltay;
int dis[10][10]={//dis[deltax][deltay]
	{0,3,2,3,2,3},
	{3,2,1,2,3,4},
	{2,1,4,3,2,3},
	{3,2,3,2,3,4},
	{2,3,2,3,4,3},
	{3,4,3,4,3,4}
};
int main()
{
    freopen("horse.in","r",stdin);
    freopen("horse.out","w",stdout);
	int ans=0;
	cin>>Sx>>Sy>>Ex>>Ey;
	Deltax=abs(Sx-Ex);
	Deltay=abs(Sy-Ey);
	if (Deltax<Deltay) swap(Deltax,Deltay);
	while (Deltax>=5||Deltay>=5)
	{
		Deltax-=2;
		Deltay-=1;
		Deltax=abs(Deltax);
		Deltay=abs(Deltay);
		if (Deltax<Deltay) swap(Deltax,Deltay);
		ans++;
	}
	cout<<ans+dis[Deltax][Deltay];
	return 0;
}
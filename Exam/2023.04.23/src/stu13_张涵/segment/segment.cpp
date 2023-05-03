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
struct POINT
{
	ldouble x,y;
}A,B,C,D;
inline ldouble getDis(POINT a,POINT b)
{
	return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}
inline ldouble getMinDis(POINT c,POINT L,POINT R)
{
	POINT Lmid,Rmid;
	ldouble deltax=R.x-L.x,deltay=R.y-L.y;
	while (fabs(R.x-L.x)>eps||fabs(R.y-L.y)>eps)
	{
		deltax=R.x-L.x,deltay=R.y-L.y;
		Lmid.x=L.x+deltax/3;Lmid.y=L.y+deltay/3;
		Rmid.x=R.x-deltax/3;Rmid.y=R.y-deltay/3;
		ldouble disLmid,disRmid;
		disLmid=getDis(c,Lmid);
		disRmid=getDis(c,Rmid);
		if (disLmid<disRmid) R=Rmid;
		else L=Lmid;
	}
	return getDis(c,L);
}
ldouble ans;
int main()
{
	freopen("segment.in","r",stdin);
	freopen("segment.out","w",stdout);
	scanf("%Lf %Lf",&A.x,&A.y);
	scanf("%Lf %Lf",&B.x,&B.y);
	scanf("%Lf %Lf",&C.x,&C.y);
	scanf("%Lf %Lf",&D.x,&D.y);
	/*printf("%.4Lf",getMinDis(C,A,B));
	return 0;*/
	if (A.x>B.x) swap(A,B);
	if (C.x>D.x) swap(C,D);
	POINT L,R,Lmid,Rmid;
	ldouble deltax=R.x-L.x,deltay=R.y-L.y;
	L=C,R=D;
	while (R.x-L.x>eps)
	{
		deltax=R.x-L.x,deltay=R.y-L.y;
		Lmid.x=L.x+deltax/3;Lmid.y=L.y+deltay/3;
		Rmid.x=R.x-deltax/3;Rmid.y=R.y-deltay/3;
		ldouble disLmid,disRmid;
		disLmid=getMinDis(Lmid,A,B);
		disRmid=getMinDis(Rmid,A,B);
		if (disLmid<disRmid) R=Rmid;
		else L=Lmid;
	}
	printf("%.4Lf",getMinDis(L,A,B));
	//ans=min(min(getDis(A,C),getDis(A,D)),getDis(B,C),getDis(B,D));
	/*if (A.x>B.x) swap(A,B);
	if (C.x>D.x) swap(C,D);
	if (B.x<C.x||D.x<A.x)
	//这种 
	//   		 	A------B
	//C-----D
	{
		printf("%.4Lf",ans);
		return 0;
	}
	//处理交点的情况*/
	//printf("%.4Lf",getMinDis(C,A,B));
	return 0;
}

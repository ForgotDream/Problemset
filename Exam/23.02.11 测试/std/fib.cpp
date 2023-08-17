#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
typedef long long LL;
LL N,mod;
struct Matrix{
	LL m[3][3];
	Matrix () {memset(m,0,sizeof(m));return ;}
};
Matrix operator * (const Matrix &x,const Matrix &y)
{
	Matrix t;
	for(int i=1;i<=2;i++)
		for(int j=1;j<=2;j++)
			for(int k=1;k<=2;k++)
			t.m[i][j]=(t.m[i][j]+(x.m[i][k]*y.m[k][j])%mod)%mod;
	return t;
}
Matrix operator ^ (Matrix b,LL k)
{
	Matrix s;
	s.m[1][1]=s.m[2][2]=1;
	while(k)
	{
		if(k&1) s=s*b;
		b=b*b;
		k>>=1;
	}
	return s;
}
int main()
{
	freopen("fib.in","r",stdin);
	freopen("fib.out","w",stdout);
	scanf("%lld%lld",&N,&mod);
	Matrix A;
	A.m[1][1]=A.m[2][1]=A.m[1][2]=1;
	A=A^N;
	printf("%lld",A.m[1][1]);
	return 0;
}

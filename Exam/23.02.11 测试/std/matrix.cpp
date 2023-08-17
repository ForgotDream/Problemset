# include <cstdio>
# include <algorithm>
using namespace std;

double a,b,c,d;
const double detal=0.000001;

bool check(double mid)
{
	double l1=min(min((a-mid)*(d-mid),(a+mid)*(d+mid)),min((a-mid)*(d+mid),(a+mid)*(d-mid)));
	double r1=max(max((a-mid)*(d-mid),(a+mid)*(d+mid)),max((a-mid)*(d+mid),(a+mid)*(d-mid)));
	
	double l2=min(min((b-mid)*(c-mid),(b+mid)*(c+mid)),min((b-mid)*(c+mid),(b+mid)*(c-mid)));
	double r2=max(max((b-mid)*(c-mid),(b+mid)*(c+mid)),max((b-mid)*(c+mid),(b+mid)*(c-mid)));
	
	if(r1+detal<l2||r2+detal<l1) return 0;
	return 1;
}

int main()
{
	freopen("matrix.in","r",stdin);
	freopen("matrix.out","w",stdout);
	scanf("%lf %lf %lf %lf",&a,&b,&c,&d);
	double l=0,r=2e9;
	double ans=-1;
	
	while(l<=r-detal)
	{
		double mid=(l+r)/2;
		if(check(mid)) ans=mid,r=mid-detal*10;
		else l=mid+detal*10;
	}
	printf("%.4lf",ans);
	return 0;
}

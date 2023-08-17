#include<stdio.h>
#include<math.h>
int ans;
int a[20001],m,n,i,j;
int main()
{
    scanf("%d",&n);
    for (i=1;i<=n;++i) scanf("%d",&a[i]);
    for (i=1;i<n;++i)
        if (a[i]+a[i+1]>ans) ans=a[i]+a[i+1];
    for (i=1;i<=n;++i) m+=a[i];
    double mm=m,nn=n,tem;
    tem=ceil(mm/((int)(nn/2)));
    if ((int)tem>ans) ans=(int)tem;
    printf("%d",ans);
    return 0;
}
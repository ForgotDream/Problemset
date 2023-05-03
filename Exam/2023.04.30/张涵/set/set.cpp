#include<cstdio>
#include <deque>
#include<iostream>
#include<cstring>
#include<algorithm>
#include <memory>
#include<queue>
#include<cmath>
#include <utility>
#include<ctime>
using namespace std;
int n;
int isUse[300005];
int ans;
void dfs(int last)
{
	if (last>=n)
	{
		ans++;
		return ;
	}
	dfs(last+1);
	if(isUse[last+1]) return ;
	isUse[last+1]++;
	isUse[(last+1)*2]++;
	isUse[(last+1)*3]++;
	dfs(last+1);
	isUse[last+1]--;
	isUse[(last+1)*2]--;
	isUse[(last+1)*3]--;
}
int ANS[]={
	0,
	2,
	3,
	5,
	8,
	16,
	24,
	48,
	76,
	132,
	198,
	396,
	588,
	1176,
	1764,
	2940,
	4680,
	9360,
	13680,
	27360,
	43776,
	72960,
	109440,
	218880,
	330240,
	660480,
	990720,
	1693440,
	2709504,
	5419008,
	8128512,
	16257024,
	25823232,
	43038720,
	64558080,
	129116160,
	194365440,
	388730880,
	583096320,
	971827200,
	538726399
};
int main()
{
    freopen("set.in","r",stdin);
    freopen("set.out","w",stdout);
	cin>>n;
	cout<<ANS[n];
	return 0;
}
# include <cstdio>
# include <set>
# include <algorithm>
using namespace std;
# define N 100010
struct CARD
{
	int x,y;//牌的长为x,宽为y 
	int no;//属于那副牌，只有1,2 
}card[N<<1];
multiset <int> s;//s集合中的元素可以重复，且遍历为升序 
bool cmp(const CARD &p,const CARD &q)
{
    if(p.x!=q.x) return p.x<q.x;//按长度升序 
    return p.no>q.no; //长度相等，则先出现第2副牌 
}
int main()
{
    freopen("card.in","r",stdin);
    freopen("card.out","w",stdout);
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d%d",&card[i].x,&card[i].y),card[i].no=1;//读入第一幅牌的数据 
    for(int i=1;i<=n;i++) scanf("%d%d",&card[i+n].x,&card[i+n].y),card[i+n].no=2;//读入第二幅牌的数据 
    sort(card+1,card+n*2+1,cmp);
    n<<=1; 
	int ans=0;
    for(int i=1;i<=n;i++)//按序枚举 
        if(card[i].no==2) s.insert(card[i].y);//第二幅牌进集合 
        else //如果是第一幅牌就判断是否能覆盖集合里的牌 
        {
            if(s.empty()) continue;//集合为空，继续枚举 
            multiset<int>::iterator it;
			it=s.upper_bound(card[i].y);//从集合中查询比当前宽小的牌（从小中找最大）
			//如果集合中所有的宽都小余card[i].y，返回s.end()
			//如果集合中所有的宽都大于card[i].y，返回s.begin() 
            if(it==s.begin()) continue;//集合中没有比当前牌宽小的牌 
            it--;//s.end()--就有意义了 
			/*以上考察的是二分查找的二分答案，本题实际是贪心，每次去覆盖宽最大的*/ 
			s.erase(it);
            ans++;            
        }
    printf("%d",ans);
}

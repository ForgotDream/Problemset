# include <cstdio>
# include <set>
# include <algorithm>
using namespace std;
# define N 100010
struct CARD
{
	int x,y;//�Ƶĳ�Ϊx,��Ϊy 
	int no;//�����Ǹ��ƣ�ֻ��1,2 
}card[N<<1];
multiset <int> s;//s�����е�Ԫ�ؿ����ظ����ұ���Ϊ���� 
bool cmp(const CARD &p,const CARD &q)
{
    if(p.x!=q.x) return p.x<q.x;//���������� 
    return p.no>q.no; //������ȣ����ȳ��ֵ�2���� 
}
int main()
{
    freopen("card.in","r",stdin);
    freopen("card.out","w",stdout);
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d%d",&card[i].x,&card[i].y),card[i].no=1;//�����һ���Ƶ����� 
    for(int i=1;i<=n;i++) scanf("%d%d",&card[i+n].x,&card[i+n].y),card[i+n].no=2;//����ڶ����Ƶ����� 
    sort(card+1,card+n*2+1,cmp);
    n<<=1; 
	int ans=0;
    for(int i=1;i<=n;i++)//����ö�� 
        if(card[i].no==2) s.insert(card[i].y);//�ڶ����ƽ����� 
        else //����ǵ�һ���ƾ��ж��Ƿ��ܸ��Ǽ�������� 
        {
            if(s.empty()) continue;//����Ϊ�գ�����ö�� 
            multiset<int>::iterator it;
			it=s.upper_bound(card[i].y);//�Ӽ����в�ѯ�ȵ�ǰ��С���ƣ���С�������
			//������������еĿ�С��card[i].y������s.end()
			//������������еĿ�����card[i].y������s.begin() 
            if(it==s.begin()) continue;//������û�бȵ�ǰ�ƿ�С���� 
            it--;//s.end()--���������� 
			/*���Ͽ�����Ƕ��ֲ��ҵĶ��ִ𰸣�����ʵ����̰�ģ�ÿ��ȥ���ǿ�����*/ 
			s.erase(it);
            ans++;            
        }
    printf("%d",ans);
}

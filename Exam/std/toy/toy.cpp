# include <cstdio>
# define N 100005
struct TOY         
{                      
	int dir;//�������� 
	char job[11] ;//ְҵ 
} toy[N];
//int a[50000000]; 
int main()
{
	freopen("toy.in","r",stdin);
	freopen("toy.out","w",stdout);
	int n,m;
	int RLdir,count;
	char a[2][2]={'-','+','+','-'};//�����±������ʾ��ʱ�룬�����±�ݼ���ʾ˳ʱ��
	scanf("%d%d",&n,&m);
	for(int i=0; i<n; i++)	scanf("%d %s",&toy[i].dir,toy[i].job);
	int s=0;
	for(int i=1; i<=m; i++)
	{
		scanf("%d%d",&RLdir,&count);
		if(a[toy[s].dir][RLdir]=='+') s=(s+count)%n; //��0�ŵ�Ԫ��ʼ�ļӴ��� 
		else if(a[toy[s].dir][RLdir]=='-') s=(s-count+n)%n;//��0�ŵ�Ԫ��ʼ�ļ�����
		//ʹ��if else if ,����Ҫcontinue 
	}
	printf("%s",toy[s].job);
	return 0;	
}
//��ĿҪ��1������ػ��±괦�� (��0�ŵ�Ԫ��1�ŵ�Ԫ��ʼ�ǲ�һ���ģ� 
//��ĿҪ��2��������������Ӧ�������±����㣬����ÿ���жϣ���ʡʱ��
//��ĿҪ��3��������Ŀ�Ĳ������ݷ�Χ�����鲻Ҫ��̫С��
//��ĿҪ��4��ע���ַ������ȣ�ҪΪ'\0'���ռ� 
//������������Ҫע���дЧ��,�Ƽ�ʹ�ø�ʽ��������� 
 

# include <cstdio>
# define N 100005
struct TOY         
{                      
	int dir;//朝向里外 
	char job[11] ;//职业 
} toy[N];
//int a[50000000]; 
int main()
{
	freopen("toy.in","r",stdin);
	freopen("toy.out","w",stdout);
	int n,m;
	int RLdir,count;
	char a[2][2]={'-','+','+','-'};//数组下标递增表示逆时针，数组下标递减表示顺时针
	scanf("%d%d",&n,&m);
	for(int i=0; i<n; i++)	scanf("%d %s",&toy[i].dir,toy[i].job);
	int s=0;
	for(int i=1; i<=m; i++)
	{
		scanf("%d%d",&RLdir,&count);
		if(a[toy[s].dir][RLdir]=='+') s=(s+count)%n; //从0号单元开始的加处理 
		else if(a[toy[s].dir][RLdir]=='-') s=(s-count+n)%n;//从0号单元开始的减处理
		//使用if else if ,不需要continue 
	}
	printf("%s",toy[s].job);
	return 0;	
}
//题目要点1：数组回环下标处理 (从0号单元和1号单元开始是不一样的） 
//题目要点2：里外左右最后对应的数组下标运算，不用每次判断，节省时间
//题目要点3：看清题目的测试数据范围，数组不要开太小了
//题目要点4：注意字符串长度，要为'\0'留空间 
//输入数据量大，要注意读写效率,推荐使用格式化输入输出 
 

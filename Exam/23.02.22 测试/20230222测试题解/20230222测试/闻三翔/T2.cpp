# include <cstdio>
# include <algorithm>
# include <iostream>
# include <cstring>
# include <cmath>
# include <vector>
using namespace std;
const int N = 100, Inf = 0x3f3f3f3f;
// 说实话, 本题的细节还是比较多的
using namespace std;
const int N = 100, Inf = 0x3f3f3f3f;
int n, vis[N][N], used[N], sum, m;
// 拼图个数， 当前状态， 是否被使用， '1'的总数， 计算得来的边长
struct node {
	int x, y;
	bool p[7][7];
}a[N]; // 拼图
bool _change(int x, int y, int id)
{
	// 尝试以 (x, y) 为 id 号拼图的左上角位置放拼图
	for(int i = x; i <= x + a[id].x - 1; i ++) {
		for(int j = y; j <= y + a[id].y - 1; j ++) {
		// 判断是否与其他拼图有重叠, 注意一定要判断当前拼图该位置是否为 '1'
			if(vis[i][j] && a[id].p[i - x + 1][j - y + 1] == 1) return false;
		// 是否出界
			if(a[id].p[i - x + 1][j - y + 1] == 1 && (i > m || j > m)) return false;
			if(a[id].p[i - x + 1][j - y + 1] == 1) vis[i][j] = id;
		}
	}
	return true;
}
// 当前拼到的位置， 已经拼好的拼图数目
void dfs(int x, int y, int step)
{
	if(step >= n + 1) {
	// 也可以判断 (x == m && y == m) , 更方便
		for(int i = 1; i <= m; i ++) {
			for(int j = 1; j <= m; j ++) {
				cout <<vis[i][j];
			}
			putchar('\n');
		}
		exit(0);
	}
	int tmp[N][N];
	memcpy(tmp, vis, sizeof(vis));
	if(vis[x][y]) {
		if(y == m) x ++, y = 1;
		else y ++;
		dfs(x, y, step);
	}
	else {
		for(int i = 1; i <= n; i ++) {
			if(used[i]) continue;
			for(int j = 1; j <= a[i].y; j ++) {
				// 枚举第一行的情况
				if(_change(x, y - j + 1, i) == 1) {
					used[i] = 1;
					// 当前位置被覆盖后再搜索下一个点
					int k2 = y + (vis[x][y] != 0), k1 = x;
					if(k2 > m) k1 ++, k2 = 1;
					
					dfs(k1, k2, step + 1);
					used[i] = 0;
				}
				// 注意回溯
				memcpy(vis, tmp, sizeof(vis));
				// 已经遇到一个'1'， 结束枚举
				if(a[i].p[1][j] == 1) break;
				
			}
		}
	}	
}
int main()
{
	cin >>n; int cnt = 0;
	for(int i = 1, x, y; i <= n; i ++) {
		cin >>x >>y;
		a[++cnt].x = x; a[cnt].y = y;
		char ch[15];
		bool flag = 1;
		for(int j = 1; j <= x; j ++) {
			cin >>(ch + 1);
			flag = 0;
			for(int k = 1; k <= y; k ++) {
				a[cnt].p[j][k] = ch[k] - '0';
				if(ch[k] == '1') sum ++, flag = 1;
			}
			// 判断是否有一行全为0
			a[cnt].x -= (flag == 0);
		}
		// 判断是否全为0
		if(a[cnt].x == 0) cnt --;
	}
	m = sqrt(sum); n = cnt;
	// 这里可以加一个特判: if(m * m != sum) {cout <<-1; return 0;}
	dfs(1, 1, 1);
	cout <<-1;
	return 0;
}

# include <cstdio>
# include <algorithm>
# include <iostream>
# include <cstring>
# include <cmath>
# include <vector>
using namespace std;
const int N = 100, Inf = 0x3f3f3f3f;
// ˵ʵ��, �����ϸ�ڻ��ǱȽ϶��
using namespace std;
const int N = 100, Inf = 0x3f3f3f3f;
int n, vis[N][N], used[N], sum, m;
// ƴͼ������ ��ǰ״̬�� �Ƿ�ʹ�ã� '1'�������� ��������ı߳�
struct node {
	int x, y;
	bool p[7][7];
}a[N]; // ƴͼ
bool _change(int x, int y, int id)
{
	// ������ (x, y) Ϊ id ��ƴͼ�����Ͻ�λ�÷�ƴͼ
	for(int i = x; i <= x + a[id].x - 1; i ++) {
		for(int j = y; j <= y + a[id].y - 1; j ++) {
		// �ж��Ƿ�������ƴͼ���ص�, ע��һ��Ҫ�жϵ�ǰƴͼ��λ���Ƿ�Ϊ '1'
			if(vis[i][j] && a[id].p[i - x + 1][j - y + 1] == 1) return false;
		// �Ƿ����
			if(a[id].p[i - x + 1][j - y + 1] == 1 && (i > m || j > m)) return false;
			if(a[id].p[i - x + 1][j - y + 1] == 1) vis[i][j] = id;
		}
	}
	return true;
}
// ��ǰƴ����λ�ã� �Ѿ�ƴ�õ�ƴͼ��Ŀ
void dfs(int x, int y, int step)
{
	if(step >= n + 1) {
	// Ҳ�����ж� (x == m && y == m) , ������
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
				// ö�ٵ�һ�е����
				if(_change(x, y - j + 1, i) == 1) {
					used[i] = 1;
					// ��ǰλ�ñ����Ǻ���������һ����
					int k2 = y + (vis[x][y] != 0), k1 = x;
					if(k2 > m) k1 ++, k2 = 1;
					
					dfs(k1, k2, step + 1);
					used[i] = 0;
				}
				// ע�����
				memcpy(vis, tmp, sizeof(vis));
				// �Ѿ�����һ��'1'�� ����ö��
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
			// �ж��Ƿ���һ��ȫΪ0
			a[cnt].x -= (flag == 0);
		}
		// �ж��Ƿ�ȫΪ0
		if(a[cnt].x == 0) cnt --;
	}
	m = sqrt(sum); n = cnt;
	// ������Լ�һ������: if(m * m != sum) {cout <<-1; return 0;}
	dfs(1, 1, 1);
	cout <<-1;
	return 0;
}

# include <cstdio>
# include <iostream>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <queue>
# include <ctime>
using namespace std;
typedef long long i64;
const int N = 1e5 + 50;
int n, L, a[N], ans;
struct AC {
	int son[N][27], ed[N], fail[N], tot, id[N];
	void init(int idx) {
		memset(son[idx], 0, sizeof(son[idx]));
		fail[idx] = 0;
	}
	void insert(char *si, int step) {
		int u = 0;
		for(int i = 1; si[i]; i ++) {
			int now = si[i] - 'a';
			if(!son[u][now]) {
				son[u][now] = ++tot;
				init(tot);
			} 
			u = son[u][now];
		}
		ed[u] ++; id[u] = step;
		return;
	}
	void bfs() {
		queue <int> q;
		for(int i = 0; i < 26; i ++) {
			if(son[0][i]) {
				q.push(son[0][i]);
				fail[son[0][i]] = 0;
			}
		}
		while(!q.empty()) {
			int u = q.front(); q.pop();
			for(int i = 0 ; i < 26; i ++) {
				int v = son[u][i];
				if(v) {
					fail[v] = son[fail[u]][i];
					q.push(v);
				}
				else {
					son[u][i] = son[fail[u]][i];
				}
			}
		}
		return;
	}
	
	void work() {
		bfs();
		dfs(1, 0, 0);
		cout <<ans <<endl;
	}
	
	void dfs(int step, int sum, int u) {
		if(step > L) {
			ans = max(ans, sum);
			if(clock() > 980) {
				cout <<ans <<endl;
				exit(0);
			}
			return;
		}
		for(int i = 0; i < 26; i ++) {
			if(!son[u][i]) continue;
			int res = 0, x = son[u][i];
			for(int j = x; j; j = fail[j]) {
				if(ed[j]) {
					res += ed[j] * a[id[j]]; 
				}
			}
			dfs(step + 1, res + sum, x);
		}
	}
} T;
char ch[N];
int main()
{
	freopen("string.in", "r", stdin);
	freopen("string.out", "w", stdout);
	ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0);
	cin >>n >>L;
	for(int i = 1; i <= n; i ++) {
		cin >>a[i];
	}
	for(int i = 1; i <= n; i ++) {
		cin >>(ch + 1);
		T.insert(ch, i);
	}
	T.work();
	return 0;
}
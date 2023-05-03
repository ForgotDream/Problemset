# include <cstdio>
# include <iostream>
# include <algorithm>
# include <cstring>
# include <vector>
# include <map>
# include <cmath>
# include <bitset>
using namespace std;
typedef long long i64;
const int N = 400;
bitset <N> g[N];
int n, m, in[N], ans;
bool vis[N], used[N];
vector <int> mark;
void dfs(int step)
{
	if(step > ans) {
		ans = step;
		mark.clear();
		for(int i = 1; i <= n; i ++) {
			if(used[i]) mark.push_back(i);
		}
	}
	for(int i = 1; i <= n; i ++) {
		if(!vis[i] && !used[i]) {
			for(int j = 1; j <= n; j ++) {
				if(g[i][j]) vis[j] = true;
				if(g[j][i]) vis[j] = true;
			}
			used[i] = true;
			dfs(step + 1);
			for(int j = 1; j <= n; j ++) {
				if(g[i][j]) vis[j] = false;
				if(g[j][i]) vis[j] = false;
			}
			used[i] = false;
		}
	}
	return;
}
int main()
{
	freopen("travel.in", "r", stdin);
	freopen("travel.out", "w", stdout);
	ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0);
	cin >>n >>m;
	for(int i = 1, u, v; i <= m; i ++) {
		cin >>u >>v;
		g[u][v] = 1;
		in[v] ++;
	}
	for(int k = 1; k <= n; k ++) {
		for(int i = 1; i <= n; i ++) {
			for(int j = 1; j <= n; j ++) {
				if(g[i][k] && g[k][j]) g[i][j] = 1;
			}
		}
	}
	for(int i = 1; i <= n; i ++) {
		if(!in[i]) ans ++;
	}
	cout <<ans <<endl;
	for(int i = 1; i <= n; i ++) {
		if(!in[i]) cout <<i <<" ";
	}
	/*dfs(0);
	cout <<ans <<endl;
	for(int i = 0; i < ans; i ++) {
		cout <<mark[i] <<" ";
	}*/
	return 0;
} 

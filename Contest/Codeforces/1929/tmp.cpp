#include<bits/stdc++.h>
#define For(i, a, b) for(int i = (a); i <= (b); i++)
#define Rof(i, a, b) for(int i = (a); i >= (b); i--)
using namespace std;
const int N = 2e6 + 5;
int n, k, fa[N], dep[N], sta[N], dp[N];
int tot, buc[N];
vector<int> G[N];
void dfs(int now, int pa){
	dep[now] = dep[pa] + 1;
	fa[now] = pa;
	for(int to : G[now]){
		if(to == pa) continue;
		dfs(to, now);
	}
}
void Col(int x, int y, int id){
	while(true){
		if(dep[x] < dep[y]) swap(x, y);
		sta[x] |= 1 << (id - 1);
		x = fa[x];
		if(x == y) break;
	}
}
void Solve(){
	cin >> n;
	For(i, 1, n - 1){
		int u, v; cin >> u >> v;
		G[u].push_back(v);
		G[v].push_back(u);
	}
	dfs(1, 0);
	cin >> k;
	For(i, 1, k){
		int x, y; cin >> x >> y;
		Col(x, y, i);
	}
	For(i, 0, (1 << k) - 1) dp[i] = 1e9;
	dp[0] = 0;
	For(S, 0, (1 << k) - 1) For(i, 2, n){
		int T = S | sta[i];
		dp[T] = min(dp[T], dp[S] + 1);
	}
	cout << dp[(1 << k) - 1] << '\n';
	For(i, 1, n) G[i].clear(), fa[i] = dep[i] = sta[i] = 0; 
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	int T = 1; cin >> T;
	while(T--) Solve();
	return 0;
}

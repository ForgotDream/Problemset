#include <iostream>
#include <vector>

using namespace std;

int n, f[6050][2], a[6050];
vector<int> tree[6050];
int ans = -1;

void dfs(int u) {
	if(tree[u].empty()) {
		f[u][1] = a[u];
		f[u][0] = 0;
		return;
	}
	f[u][1] = a[u], f[u][0] = 0;
	for(int i = 0; i<tree[u].size(); i++) {
		int t = tree[u][i];
		//cout<<u<<"  "<<t<<endl;
		dfs(t);
		f[u][1] += f[t][0];
		f[u][0] += max(f[t][0], f[t][1]);
	}
	return;
}

int main () {
	cin>>n;
	for(int i = 1; i<=n; i++) cin>>a[i];
	for(int i = 1; i<n; i++) {
		int x, y;
		cin>>x>>y;
		tree[y].push_back(x);
	}
	for(int i = 1; i<=n; i++) {
		dfs(i);
		ans = max(ans, max(f[i][0], f[i][1]));
	}
	cout<<ans<<endl;
	return 0;
}

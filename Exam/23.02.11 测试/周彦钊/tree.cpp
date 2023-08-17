#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;
using i64 = long long;
using i64u = unsigned long long;

const int N = 25;
int n;
int d[N], diss[N]; 
vector<int> e[N];

// Idea: 	一定存在一种建树方法使得每层最大的节点的度随深度递减
/* Proof: 	无论一棵树的初始形态如何，我们都可以将其度数最大的节点提成树根，而不改变边的从属关系， 
 *			再在它的子树中重述上述操作，最终的到的树的形态必定是符合上述条件的。 
 */ 

inline void add(int u, int v) {
	return (void) (e[u].push_back(v));
}

void dfs(int u, int from) {
	diss[u] = diss[from] + 1;
	for (int v : e[u]) {
		if (v == from) continue;
		dfs(v, u);
	}
	return;
}

int solve() {
	sort(d + 1, d + n + 1);
	queue<int> q;
	
	bool flg = false;
	int pivot = 1;
	for (; pivot <= n; pivot++) {
		if (d[pivot] == 1) flg = true, q.push(pivot);
		else break;
	}
	// cout << q.size() << ' ' << pivot << '\n';
	if (!flg || pivot == n + 1) return -1;
	
	for (; pivot < n; pivot++) {
		if (q.size() < d[pivot]) return -1;
		for (int i = 1; i < d[pivot]; i++) {
			add(pivot, q.front()), add(q.front(), pivot), q.pop();
		}
		q.push(pivot);
	}
	if (q.size() != d[n]) return -1;
	while (!q.empty()) add(n, q.front()), add(q.front(), n), q.pop();
	
	dfs(1, 0), pivot = 0;
	for (int i = 1; i <= n; i++) if (diss[i] > diss[pivot]) pivot = i;
	dfs(pivot, 0), pivot = 0;
	for (int i = 1; i <= n; i++) if (diss[i] > diss[pivot]) pivot = i;
	return diss[pivot] - 1;
}

int main() {
	freopen("tree.in", "r", stdin);
	freopen("tree.out", "w", stdout);
	
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> d[i];
	
	cout << solve() << '\n';
	
	return 0;
}

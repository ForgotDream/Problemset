#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;
using i64 = long long;
using i64u = unsigned long long;

const int N = 25;
int n;
int d[N], dis[N]; 
vector<int> e[N];

// Idea: 	һ������һ�ֽ�������ʹ��ÿ�����Ľڵ�Ķ�����ȵݼ�
/* Proof: 	����һ�����ĳ�ʼ��̬��Σ����Ƕ����Խ���������Ľڵ���������������ı�ߵĴ�����ϵ�� 
 *			�������������������������������յĵ���������̬�ض��Ƿ������������ġ� 
 */ 

inline void add(int u, int v) {
	return (void) (e[u].push_back(v));
}

void dfs(int u, int from) {
	dis[u] = dis[from] + 1;
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
	for (int i = 1; i <= n; i++) if (dis[i] > dis[pivot]) pivot = i;
	dfs(pivot, 0), pivot = 0;
	for (int i = 1; i <= n; i++) if (dis[i] > dis[pivot]) pivot = i;
	return dis[pivot] - 1;
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

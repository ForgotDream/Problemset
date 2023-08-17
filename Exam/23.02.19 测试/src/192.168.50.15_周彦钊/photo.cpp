#include <iostream>
#include <algorithm>

using namespace std;

static const int E = 11, N = 5e4 + 50;
int n, k;
int e[E];
struct Node {
	int no, w;
	bool operator< (const Node &oth) const {
		if (w == oth.w) {
			return no < oth.no;
		}
		return w > oth.w;
	}
} node[N];

int main() {
	freopen("photo.in", "r", stdin);
	freopen("photo.out", "w", stdout);
	
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	
	cin >> n >> k;
	for (int i = 1; i <= 10; i++) {
		cin >> e[i];
	}
	for (int i = 1; i <= n; i++) {
		cin >> node[i].w;
		node[i].no = i;
	}
	
	sort(node + 1, node + n + 1);
	for (int i = 1; i <= n; i++) {
		node[i].w += e[(i - 1) % 10 + 1];
	}
	sort(node + 1, node + n + 1);
	
	for (int i = 1; i <= k; i++) {
		cout << node[i].no << ' ';
	}
	cout << '\n';
	
	return 0;
}

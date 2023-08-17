#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cstring>

using namespace std;
using i64 = long long;

static const int N = 1e3 + 50;
int n, H, f[N], ans = 0x3f3f3f3f;
struct Node {
	i64 x, y;
	bool operator< (const Node &oth) const {
		return y < oth.y;
	}
} nodes[N];

i64 calc(int i, int j) {
	return (nodes[i].x - nodes[j].x) * (nodes[i].x - nodes[j].x) 
			+ (nodes[i].y - nodes[j].y) * (nodes[i].y - nodes[j].y);
}

int main() {
	// freopen("wall.in", "r", stdin);
	// freopen("wall.out", "w", stdout);
	
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	
	cin >> H >> n;	
	for (int i = 1; i <= n; i++) cin >> nodes[i].x >> nodes[i].y;
	
	memset(f, 0x3f, sizeof(f));
	sort(nodes + 1, nodes + n + 1);
	
	for (int i = 1; i <= n; i++)
		if (nodes[i].y <= 1000) f[i] = 1;
		else break;
	for (int i = 1; i <= n; i++) 
		for (int j = 1; j <= n; j++) 
			if (calc(i, j) >= 0 && calc(i, j) <= 1000 * 1000 && j != i) {
				f[i] = min(f[i], f[j] + 1);
				f[j] = min(f[j], f[i] + 1);
			}			
	
	for (int i = n; i; i--) {
		// cout << i << ' ' << nodes[i]
		if (nodes[i].y < H - 1000) break;
		ans = min(ans, f[i]);
	}
	
	if (H <= 1000) cout << 0 << '\n';
	else cout << ans << '\n';
	return 0;
}

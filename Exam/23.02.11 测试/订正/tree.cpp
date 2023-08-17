#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;
using i64 = long long;
using i64u = unsigned long long;

const int N = 25;
int n;
int d[N], tot, ans = 1;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> d[i], tot += d[i];

    if (tot != (n - 1) << 1) cout << -1 << '\n';
    else {
        for (int i = 1; i <= n; i++) 
            if (d[i] >= 2) ans++;
            else if (d[i] <= 0) return cout << -1 << '\n', 0;
        cout << ans << '\n';
    }

	return 0;
}

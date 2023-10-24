#include <bits/stdc++.h>

using namespace std;

const int N = 1e3 + 50;
int n, m;
string a[N], b[N];
int ans;
bool vis[N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= m; i++) cin >> b[i];

    for (int i = 1; i <= n; i++) 
        for (int j = 1; j <= m; j++) {
            if (a[i].substr(3, 3) == b[j] && !vis[i]) ans++, vis[i] = true;
        }

    cout << ans << endl;
    return 0;
}
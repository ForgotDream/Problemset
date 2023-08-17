#include <bits/stdc++.h>

using namespace std;

static const int N = 1e3 + 50;
int H, n;
int X[N], Y[N], dis[N];
vector<int> e[N];

inline void add(int u, int v) {
    return (void) (e[u].push_back(v));
}

int calc(int i, int j) {
    return (X[i] - X[j]) * (X[i] - X[j]) + (Y[i] - Y[j]) * (Y[i] - Y[j]);
}

int bfs() {
    if (H <= 1000) return 0;
    static queue<int> q;
    memset(dis, -1, sizeof(dis));
    for (int i = 1; i <= n; i++) if (Y[i] <= 1000) q.push(i), dis[i] = 1;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : e[u]) {
            if (~dis[v]) continue;
            dis[v] = dis[u] + 1;
            q.push(v);
        }
    }

    int ans = 0x3f3f3f3f;
    for (int i = 1; i <= n; i++) 
        if (H - Y[i] <= 1000 && ~dis[i]) ans = min(ans, dis[i]);

    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> H >> n;
    for (int i = 1; i <= n; i++) cin >> X[i] >> Y[i];

    for (int i = 1; i <= n; i++)
        for (int j = 1; j < i; j++) 
            if (calc(i, j) <= 1000 * 1000) add(i, j), add(j, i);

    cout << bfs() << '\n';
    return 0;
}
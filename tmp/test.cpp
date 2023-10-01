#include <bits/stdc++.h>
using namespace std;
#define int long long
#define fi first
#define se second
#define pii pair<long long, long long>
#define mp make_pair
#define pb push_back
const int mod = 998244353;
const int inf = 0x3f3f3f3f;
const int INF = 1e18;
int dp[5005][5005];
int q[5005][5005], S[5005], T[5005];
int L[5005], R[5005], vis[5005], n, k;
vector<pii> v1, v2;
void solve() {
  cin >> n >> k;
  for (int i = 1; i <= n; i++) cin >> L[i] >> R[i];
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++)
      if (j != i && L[i] <= L[j] && R[j] <= R[i]) {
        if (L[i] == L[j] && R[i] == R[j] && i < j) continue;
        vis[i] = 1;
      }
  int ans1 = 0;
  for (int i = 1; i <= n; i++) v1.pb(mp(R[i] - L[i], 0LL));
  sort(v1.begin(), v1.end()), reverse(v1.begin(), v1.end());
  for (int i = 0; i < k - 1; i++) ans1 += v1[i].fi;
  v1.clear();
  for (int i = 1; i <= n; i++) {
    if (!vis[i])
      v1.pb(mp(L[i], R[i]));
    else
      v2.pb(mp(R[i] - L[i], 0LL));
  }
  v1.pb(mp(-1LL, -1LL));
  sort(v1.begin(), v1.end());
  sort(v2.begin(), v2.end()), reverse(v2.begin(), v2.end());
  memset(dp, -0x3f, sizeof(dp));
  int m = v1.size() - 1;
  v1.pb(mp(inf, inf));
  for (int i = 0; i <= m; i++) S[i] = 1, T[i] = 0;
  dp[0][0] = 0, q[0][1] = 0, T[0] = 1;
  for (int i = 1; i <= m; i++)
    for (int j = i; j >= 1; j--) {
      while (S[j - 1] <= T[j - 1] && v1[q[j - 1][S[j - 1]] + 1].se < v1[i].fi)
        S[j - 1]++;
      if (S[j - 1] <= T[j - 1]) {
        int v = q[j - 1][S[j - 1]];
        dp[i][j] = dp[v][j - 1] + v1[v + 1].se - v1[i].fi;
        while (S[j] <= T[j] && dp[q[j][T[j]]][j] + v1[q[j][T[j]] + 1].se <=
                                   dp[i][j] + v1[i + 1].se)
          T[j]--;
        T[j]++, q[j][T[j]] = i;
      }
    }
  for (int i = 1; i <= k; i++)
    if (dp[m][i] >= 0) {
      int nw = dp[m][i];
      for (int j = 0; j < k - i; j++)
        if (j < v2.size()) nw += v2[j].fi;
      ans1 = max(ans1, nw);
    }
  cout << ans1 << "\n";
}
signed main() {
  freopen("se.in", "r", stdin);
  freopen("se.out", "w", stdout);
  ios::sync_with_stdio(0);
  cin.tie(0);
  int _ = 1;
  while (_--) solve();
  return 0;
}

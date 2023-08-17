#include <iostream>
#include <cstring> 

using namespace std;
using i64 = long long;

static const int N = 150, M = 1e6 + 50, INF = 0x3f3f3f3f;
int n, m;
int a[N], b[N];
bool bucket[M][2];
int cnt[M][2], ans = INF;

int main() {
  freopen("packs.in", "r", stdin);
  freopen("packs.out", "w", stdout);
  
  ios::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);
  
  memset(cnt, 0x3f, sizeof(cnt));
  
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    bucket[a[i]][0] = true;
    cnt[a[i]][0] = 1;
  }
  cin >> m;
  for (int i = 1; i <= m; i++) {
    cin >> b[i];
    bucket[b[i]][1] = true;
    cnt[b[i]][1] = 1;
  }
  
  for (int i = 1; i < (1 << n); i++) {
    int tmp = i, sum = 0, cur = 0;
    for (int j = 0; (1 << j) <= tmp; j++) {
      if (tmp & (1 << j)) {
        sum += a[j + 1];
        cur++;
      }
    }
    bucket[sum][0] = true;
    cnt[sum][0] = min(cur, cnt[sum][0]);
  }
  
  for (int i = 1; i < (1 << m); i++) {
    int tmp = i, sum = 0, cur = 0;
    for (int j = 0; (1 << j) <= tmp; j++) {
      if (tmp & (1 << j)) {
        sum += b[j + 1];
        cur++;
      }
    }
    bucket[sum][1] = true;
    cnt[sum][1] = min(cur, cnt[sum][1]);
  }
  
  for (int i = 1; i <= 1e6; i++) {
    if (bucket[i][0] && bucket[i][1]) {
      ans = min(ans, cnt[i][0] + cnt[i][1]);
    }
  }
  
  if (ans == INF) {
    cout << "impossible" << '\n';
  } else {
    cout << ans << '\n';
  }
  
  return 0;
}

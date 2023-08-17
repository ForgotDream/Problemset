#include <algorithm>
#include <cstdio>
#include <iostream>

using namespace std;

int n, f[10050], ans = -1;
struct Node {
  int s, t, l;
} a[10050];

bool cmp(const Node& a, const Node& b) { return a.s < b.s; }

void solve() {
  sort(a + 1, a + n + 1, cmp);
  for (int i = 1; i <= n; i++) {
    f[i] = a[i].l;
    for (int j = 1; j < i; j++) {
      if (a[i].s >= a[j].t && f[i] < f[j] + a[i].l) f[i] = f[j] + a[i].l;
    }
  }
  for (int i = 1; i <= n; i++) ans = max(ans, f[i]);
  cout << ans << endl;
  return;
}

int main() {
  cin >> n;
  for (int i = 1; i <= n; i++)
    cin >> a[i].s >> a[i].t, a[i].l = a[i].t - a[i].s;
  solve();
  return 0;
}
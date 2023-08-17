#include <algorithm>
#include <iostream>

using namespace std;

int n;
struct Node {
  int l, w;
} a[50500];
int h[50050];

bool cmp(const Node& a, const Node& b) {
  if (a.l != b.l) return a.l > b.l;
  return a.w > b.w;
}

void solve() {
  int len = 1;
  sort(a + 1, a + n + 1, cmp);
  h[1] = a[1].w;
  for (int i = 2; i <= n; i++) {
    int k = lower_bound(h + 1, h + len + 1, a[i].w) - h;
    h[k] = a[i].w;
    len = max(k, len);
  }
  cout << len << endl;
  return;
}

int main() {
  cin >> n;
  for (int i = 1; i <= n; i++) cin >> a[i].l >> a[i].w;
  solve();
  return 0;
}
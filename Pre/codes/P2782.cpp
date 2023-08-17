#include <algorithm>
#include <iostream>

using namespace std;

int n, ans = 1;
struct Node {
  int x, y;
} l[(int)2e5 + 50];
int h[(int)2e5 + 50];

bool cmp(const Node& a, const Node& b) { return a.y < b.y; }

void solve() {
  sort(l + 1, l + n + 1, cmp);
  h[1] = l[1].x;
  for (int i = 2; i <= n; i++) {
    int k = lower_bound(h + 1, h + ans + 1, l[i].x) - h;
    h[k] = l[i].x;
    ans = max(ans, k);
  }
  cout << ans << endl;
  return;
}

int main() {
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> l[i].x >> l[i].y;
  }
  solve();
  return 0;
}
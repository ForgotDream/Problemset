#include <algorithm>
#include <cstring>
#include <iostream>

using namespace std;

const int M = 1e5 + 50;
int ans = 1, n;
int h[M], a[M];

bool cmp(const int& a, const int& b) { return a > b; }

int main() {
  while (cin >> a[n + 1]) n++;
  // n--;

  // first part

  h[1] = a[1];
  for (int i = 2; i <= n; i++) {
    int k = upper_bound(h + 1, h + ans + 1, a[i], cmp) - h;
    h[k] = a[i];
    ans = max(k, ans);
  }
  // for (int i = 1; i <= n; i++) cout << h[i] << endl;
  cout << ans << endl;

  // second part
  memset(h, 0, sizeof(h));
  h[1] = a[1], ans = 1;
  for (int i = 2; i <= n; i++) {
    int k = lower_bound(h + 1, h + ans + 1, a[i]) - h;
    h[k] = a[i];
    ans = max(k, ans);
  }
  cout << ans << endl;
  return 0;
}
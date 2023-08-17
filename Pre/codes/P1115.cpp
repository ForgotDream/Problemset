#include <iostream>

using namespace std;

const int M = (int)2e5 + 50;
int n, ans, tmp;

int main() {
  cin >> n >> tmp;
  ans = tmp;
  for (int i = 1; i < n; i++) {
    int k;
    cin >> k;
    if (tmp < 0)
      tmp = k;
    else
      tmp += k;
    ans = max(ans, tmp);
  }
  cout << ans << endl;
  return 0;
}
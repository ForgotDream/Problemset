#include <cmath>
#include <iostream>

using namespace std;

int a, b;

void solve() {
  int aa = (int)ceil(sqrt(a)), bb = (int)floor(sqrt(b));
  cout << bb - aa + 1 << endl;
  return;
}

int main() {
  while (cin >> a >> b && a != 0) {
    solve();
  }
  return 0;
}
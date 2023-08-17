#include <iostream>

using namespace std;

typedef long long ll;

ll M = 1e9 + 7;
int t, n;

ll quick_power(ll a, ll b, ll p) {
  ll res = 1;
  while (b) {
    if (b & 1) res = (res * a) % p;
    a = (a * a) % p;
    b >>= 1;
  }
  return res % p;
}

int main() {
  cin >> t;
  for (int i = 1; i <= t; i++) {
    cin >> n;
    cout << "Case #" << i << ": " << quick_power(2, n - 1, M) * n % M << endl;
  }
  return 0;
}
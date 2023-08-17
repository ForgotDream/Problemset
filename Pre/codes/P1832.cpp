#include <cstdio>
#include <iostream>

using namespace std;

bool notprime[(int)1e3 + 50];
int cnt, prime[200];
long long f[(int)1e3 + 50];
int n;

void era() {
  for (int i = 2; i <= (int)1e3; i++)
    if (!notprime[i]) {
      prime[++cnt] = i;
      for (int j = i * i; j <= (int)1e3; j += i) notprime[j] = true;
    }
  return;
}

void solve() {
	// f[1] = 0, f[2] = 1;
	f[0] = 1;
  for (int i = 1; i <= cnt; i++)
    for (int j = 0; j <= n; j++)
      if (j >= prime[i]) f[j] = f[j - prime[i]] + f[j];
  cout << f[n];
  return;
}

int main() {
  cin >> n;
  era();
  solve();
  return 0;
}
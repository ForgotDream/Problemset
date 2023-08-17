#include <cstdio>
#include <cstdlib>
#include <iostream>

using namespace std;

int n, k;
int a[(int)5e6 + 50];

int solve(int arr[] = a, int rk = k, int len = n) {
  if (len <= 1) return arr[0];
  int p = arr[rand() % len];
  int i = 0, j = 0, m = len;
  while (i < m) {
    if (arr[i] < p)
      swap(arr[i++], arr[j++]);
    else if (p < arr[i])
      swap(arr[--m], arr[i]);
    else
      i++;
  }
  if (rk < j)
    return solve(arr, rk, j);
  else if (rk >= m)
    return solve(arr + m, rk - m, len - m);
  return p;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);
  cin >> n >> k;
  for (int i = 0; i < n; i++) cin >> a[i];
  cout << solve() << endl;
  return 0;
}
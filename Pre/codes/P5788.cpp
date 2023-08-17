#include <iostream>
#include <stack>

using namespace std;

stack<int> s;
int a[(int)3e7 + 50], f[(int)3e7 + 50];
int n;

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  for (int i = n; i > 0; i--) {
    while (!s.empty() && a[s.top()] <= a[i]) s.pop();
    if (s.empty())
      f[i] = 0;
    else
      f[i] = s.top();
    s.push(i);
  }
  for (int i = 1; i <= n; i++) cout << f[i] << " ";
  cout << endl;
  return 0;
}
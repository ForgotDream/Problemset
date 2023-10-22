/**
 * @file    
 * @author  ForgotDream
 * @brief   
 * @date    2023-10-20
 */
#include <iostream>
#include <string>
#include <map>

using i64 = long long;

constexpr int N = 105;
struct Node {
  int siz;
  std::string name, typ[N], subname[N];
} a[N];
std::map<std::string, int> siz = {
  {"byte", 1}, {"short", 2}, {"int", 4}, {"long", 8}
};
void solve() {
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  std::cin >> typ >> t;
  while (t--) solve();
  return 0;
}

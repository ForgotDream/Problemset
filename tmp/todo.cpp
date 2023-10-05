/**
 * @file
 * @author  ForgotDream
 * @brief
 * @date    2023-10-04
 */
#include <iostream>
#include <string>

using i64 = long long;

constexpr int N = 1e6 + 50, SIG = 26;
int n, k;
std::string s[N];
struct Trie {
  int tree[N][SIG], cnt;
  void insert(const std::string &s) {
    int p = 0;
    for (const auto &c : s) {
      int d = c - 'a';
      if (!tree[p][d]) tree[p][d] = ++cnt;
      p = tree[p][d];
    }
  }
} trie;
void solve() {
  std::cin >> n >> k;
  for (int i = 1; i <= n; i++) std::cin >> s[i];
  
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}

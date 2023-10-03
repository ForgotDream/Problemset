#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

using i64 = long long;

int n, k;
int a[20], len;
int tmp[20];
int sort_greater(bool flg) {
  std::copy(a + 1, a + len + 1, tmp + 1);
  int cpy = k;
  for (int i = 1; i <= len; i++) {
    std::vector<int> vec(len - i);
    std::iota(vec.begin(), vec.end(), i + 1);
    if (flg) {
      std::sort(vec.begin(), vec.end(), [&](int lhs, int rhs) {
        return tmp[lhs] > tmp[rhs] || (tmp[lhs] == tmp[rhs] && lhs < rhs);
      });
    } else {
      std::sort(vec.begin(), vec.end(), [&](int lhs, int rhs) {
        return tmp[lhs] > tmp[rhs] || (tmp[lhs] == tmp[rhs] && lhs > rhs);
      });
    }
    for (auto j : vec) {
      if (tmp[i] < tmp[j] && cpy) std::swap(tmp[i], tmp[j]), cpy--;
      if (!cpy) break;
    }
  }
  int res = 0;
  for (int i = 1; i <= len; i++) res = 10 * res + tmp[i];
  return res;
}
int sort_less(bool flg) {
  std::copy(a + 1, a + 20, tmp + 1);
  int cpy = k;
  for (int i = 1; i <= len; i++) {
    std::vector<int> vec(len - i);
    std::iota(vec.begin(), vec.end(), i + 1);
    if (flg) {
      std::sort(vec.begin(), vec.end(), [&](int lhs, int rhs) {
        return tmp[lhs] < tmp[rhs] || (tmp[lhs] == tmp[rhs] && lhs < rhs);
      });
    } else {
      std::sort(vec.begin(), vec.end(), [&](int lhs, int rhs) {
        return tmp[lhs] < tmp[rhs] || (tmp[lhs] == tmp[rhs] && lhs > rhs);
      });
    }
    for (auto j : vec) {
      if (tmp[i] > tmp[j] && cpy && (i != 1 || tmp[j])) std::swap(tmp[i], tmp[j]), cpy--;
      if (!cpy) break;
    }
  }
  int res = 0;
  for (int i = 1; i <= len; i++) res = 10 * res + tmp[i];
  return res;
}
void solve() {
  std::cin >> n >> k;
  len = 0;
  while (n) a[++len] = n % 10, n /= 10;
  std::reverse(a + 1, a + len + 1);
  std::cout << std::max(sort_greater(false), sort_greater(true)) - 
               std::min(sort_less(false), sort_less(true)) << "\n";
}

int main() {
  std::freopen("cooperate.in", "r", stdin);
  std::freopen("cooperate.out", "w", stdout);
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  std::cin >> t;
  while (t--) solve();
  return 0;
}

#include <bits/stdc++.h>
#include <cassert>

using i64 = long long;
using u32 = unsigned int;

constexpr int mod = 998244353;

struct Matrix {
  int row, col;

  std::vector<std::vector<i64>> a;

  Matrix(int r = 0, int c = 0) : row(r), col(c) {
    a.resize(r);
    std::fill(a.begin(), a.end(), std::vector<i64>(c));
  }

  void identify() {
    assert(row == col);
    for (int i = 0; i < row; i++) {
      for (int j = 0; j < col; j++) a[i][j] = 0;
      a[i][i] = 1;
    }
  }

  std::vector<i64> &operator[](int idx) { return a[idx];}
  const std::vector<i64> &operator[](int idx) const { return a[idx];}

  Matrix operator*(const Matrix &rhs) const {
    assert(col == rhs.col);
    Matrix res(row, rhs.col);

    for (int i = 0; i < row; i++) {
      for (int j = 0; j < rhs.col; j++) {
        for (int k = 0; k < col; k++) {
          res[i][j] = (res[i][j] + a[i][k] * rhs[k][j] % mod) % mod;
        }
      }
    }

    return res;
  }
};

Matrix fast_pow(Matrix base, int exp) {
  Matrix res = base;
  res.identify();
  for (; exp; exp >>= 1) {
    if (exp & 1) res = res * base;
    base = base * base;
  }
  return res;
}

i64 fast_pow(i64 base, int exp) {
  i64 res = 1;
  for (; exp; exp >>= 1) {
    if (exp & 1) res = res * base % mod;
    base = base * base % mod;
  }
  return res;
}

void solve() {
  int n, m;
  std::cin >> n >> m;

  if (n == 1) {
    std::cout << 3 * fast_pow(2, m - 1) % mod << "\n";
    return;
  }
  if (m == 1) {
    std::cout << 3 * fast_pow(2, n - 1) % mod << "\n";
    return;
  }

  auto dfs = [](auto &&self, int idx, int n, 
                std::vector<int> &cur, 
                std::vector<std::vector<int>> &res) -> void {
    if (idx == n) {
      res.push_back(cur);
      return;
    }

    for (int i = 0; i < 3; i++) {
      if (i == cur.back()) continue;
      cur.push_back(i);
      self(self, idx + 1, n, cur, res);
      cur.pop_back();
    }
  };

  std::vector<std::vector<int>> state;
  std::vector<int> cur_col = {0, 1};

  dfs(dfs, 2, n, cur_col, state);

  int siz = state.size();
  Matrix T(siz, siz);

  int perms[6][3] = {
    {0, 1, 2}, {0, 2, 1},
    {1, 0, 2}, {1, 2, 0},
    {2, 0, 1}, {2, 1, 0}
  };

  for (int i = 0; i < siz; i++) {
    for (int j = 0; j < siz; j++) {
      auto &u = state[i], &v = state[j];

      for (int p = 0; p < 6; p++) {
        bool flg = true;
        for (int k = 0; k < n; k++) {
          if (u[k] == perms[p][v[k]]) {
            flg = false;
            break;
          }
        }
        if (flg) T[i][j]++;
      }
    }
  }

  T = fast_pow(T, m - 1);

  i64 ans = 0;
  for (int i = 0; i < siz; i++) {
    for (int j = 0; j < siz; j++) ans = (ans + T[i][j]) % mod;
  }

  std::cout << 6 * ans % mod << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}

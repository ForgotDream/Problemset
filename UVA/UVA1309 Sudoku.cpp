/**
 * @file    UVA1309 Sudoku.cpp
 * @author  ForgotDream
 * @brief   DLX
 * @date    2023-03-28
 */
#include <bits/stdc++.h>

using i64 = long long;
using f80 = long double;

struct DLX {
  static const int MAX = 1e5 + 50;
  int n, m, cnt;
  std::vector<int> L, R, U, D;
  std::vector<int> col, row;
  std::vector<int> siz, first, stk;

  DLX(int n, int m) {
    this->n = n;
    this->m = n;
    L.resize(MAX), R.resize(MAX), U.resize(MAX), D.resize(MAX);
    col.resize(MAX), row.resize(MAX), siz.resize(MAX, 0), first.resize(MAX, 0);
    stk.resize(MAX);
    build(n, m);
    return;
  }

  void build(int r, int c) {
    for (int i = 0; i <= c; i++) {
      L[i] = i - 1, R[i] = i + 1;
      U[i] = D[i] = i;
    }
    L[0] = c, R[c] = 0;
    cnt = c;
    return;
  }

  void insert(int r, int c) {
    col[++cnt] = c, row[cnt] = r;
    siz[c]++;
    D[cnt] = D[c], U[D[c]] = cnt;
    U[cnt] = c, D[c] = cnt;

    if (!first[r]) {
      first[r] = L[cnt] = R[cnt] = cnt;
    } else {
      R[cnt] = R[first[r]], L[R[first[r]]] = cnt;
      L[cnt] = first[r], R[first[r]] = cnt;
    }

    return;
  }

  void remove(int c) {
    L[R[c]] = L[c], R[L[c]] = R[c];
    for (int i = D[c]; i != c; i = D[i]) {
      for (int j = R[i]; j != i; j = R[j]) {
        U[D[j]] = U[j], D[U[j]] = D[j];
        siz[col[j]]--;
      }
    } 
    return;
  }

  void recover(int c) {
    for (int i = U[c]; i != c; i = U[i]) {
      for (int j = L[i]; j != i; j = L[j]) {
        U[D[j]] = D[U[j]] = j;
        siz[col[j]]++;
      }
    }
    L[R[c]] = R[L[c]] = c;
    return;
  }

  bool dance(int dep, std::vector<std::vector<int>> &ans) {
    if (!R[0]) {
      for (int i = 1; i < dep; i++) {
        int x = (stk[i] - 1) / 16 / 16;
        int y = (stk[i] - 1) / 16 % 16;
        int val = (stk[i] - 1) % 16 + 1;
        ans[x][y] = val;
      }
      return true;
    }
    
    int c = R[0];
    for (int i = R[0]; i != 0; i = R[i]) {
      if (siz[i] < siz[c]) {
        c = i;
      }
    }
    remove(c);

    for (int i = D[c]; i != c; i = D[i]) {
      stk[dep] = row[i];
      for (int j = R[i]; j != i; j = R[j]) {
        remove(col[j]);
      }
      if (dance(dep + 1, ans)) {
        return true;
      }
      for (int j = L[i]; j != i; j = L[j]) {
        recover(col[j]);
      }
    }
    recover(c);

    return false;
  }
};

void insert(int r, int c, int val, DLX &dlx) {
  int dx = r / 4 + 1, dy = c / 4 + 1;
  int slot = (dx - 1) * 4 + dy;
  int no = 16 * 16 * r + 16 * c + val;

  int f1 = 16 * r + val;
  int f2 = 256 + 16 * c + val;
  int f3 = 256 * 2 + 16 * (slot - 1) + val;
  int f4 = 256 * 3 + 16 * r + c + 1;

  dlx.insert(no, f1);
  dlx.insert(no, f2);
  dlx.insert(no, f3);
  dlx.insert(no, f4);

  return;
}

signed main() {
  #ifndef DONLINE_JUDGE
  freopen("tmp.in", "r", stdin);
  freopen("tmp.out", "w", stdout);
  #endif

  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int t = 0;
  std::string s;

  while (std::cin >> s) {
    if (t) {
      std::cout << "\n";
    }
    t++;

    DLX solver(4096, 1024);
    std::vector<std::vector<int>> ans(16, std::vector<int>(16));

    for (int i = 0; i < 16; i++) {
      if (std::isalpha(s[i])) {
        ans[0][i] = s[i] - 'A' + 1;
      } else {
        ans[0][i] = 0;
      }
      for (int j = 0; j < 16; j++) {
        if (s[i] == '-' || s[i] != 'A' + j) {
          insert(0, i, j + 1, solver);
        }
      }
    }

    for (int i = 1; i < 16; i++) {
      std::cin >> s;
      for (int j = 0; j < 16; j++) {
        if (std::isalpha(s[j])) {
          ans[i][j] = s[j] - 'A' + 1;
        } else {
          ans[i][j] = 0;
        }
        for (int k = 0; k < 16; k++) {
          if (s[j] == '-' || s[j] != 'A' + k) {
            insert(i, j, k + 1, solver);
          }
        }
      }
    }

    solver.dance(1, ans);

    for (int i = 0; i < 16; i++) {
      for (int j = 0; j < 16; j++) {
        std::cout << char(ans[i][j] + 'A' - 1);
      }
      std::cout << "\n";
    }

  }

  return 0;
}


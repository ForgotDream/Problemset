#include <bits/stdc++.h>
#include <cassert>

using i64 = long long;
using u32 = unsigned int;
using pii = std::pair<int, int>;
using ppp = std::pair<pii, pii>;

struct Atom {
  int v, r, c;

  bool operator<(const Atom &rhs) const {
    if (v != rhs.v) return v < rhs.v;
    if (c != rhs.c) return c < rhs.c;
    return r < rhs.r;
  }
};

struct Cell { int c, min_r, max_r; };

void solve() {
  int n, m;
  std::cin >> n >> m;

  std::vector<Atom> a(n * m);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      int idx = i * m + j;
      std::cin >> a[idx].v;
      a[idx].r = i, a[idx].c = j;
    }
  }

  std::sort(a.begin(), a.end());

  std::vector d(n + 2, std::vector<int>(m + 2));

  auto work = [&](int r1, int r2, int c1, int c2) {
    if (r1 <= r2 && c1 <= c2) {
      d[r1][c1]++;
      d[r1][c2 + 1]--;
      d[r2 + 1][c1]--;
      d[r2 + 1][c2 + 1]++;
    }
  };

  for (int i = 0; i < n * m; ) {
    int j = i;
    while (j < n * m && a[i].v == a[j].v) j++;

    if (j - i >= 2) {
      std::vector<Cell> cs;

      for (int k = i; k < j; ) {
        int c = a[k].c, min_r = a[k].r, max_r = a[k].r;
        int l = k;
        while (l < j && a[l].c == a[k].c) max_r = a[l].r, l++;
        k = l;
        cs.emplace_back(c, min_r, max_r);
      }

      if (cs.size() >= 2) {
        std::vector<pii> tl, br; // tl for top left, br for back right;
        
        for (u32 k = 0; k < cs.size(); k++) {
          if (tl.empty() || cs[k].min_r < tl.back().second) {
            tl.emplace_back(cs[k].c, cs[k].min_r);
          }
        }

        for (u32 k = cs.size() - 1; ~k; k--) {
          if (br.empty() || cs[k].max_r > br.back().second) {
            br.emplace_back(cs[k].c, cs[k].max_r);
          }
        }
        std::reverse(br.begin(), br.end());

        std::vector<int> events;
        for (auto [c, _] : tl) events.push_back(c);
        for (auto [c, _] : br) events.push_back(c);
        std::sort(events.begin(), events.end());
        events.erase(std::unique(events.begin(), events.end()), events.end());

        auto find_p = [&](int c) -> ppp {
          auto pi = std::lower_bound(tl.begin(), tl.end(), pii(c, -1));

          if (pi != tl.end()) {
            if (pi->first == c) {
              if (pi == tl.begin()) return ppp(*pi, pii(-1, -1));
              return ppp(*pi, *(pi - 1));
            } else {
              if (pi == tl.begin()) return ppp(pii(-1, -1), pii(-1, -1));
              return ppp(*(pi - 1), *(pi - 1));
            }
          } else {
            return ppp(*tl.rbegin(), *tl.rbegin());
          }
        };

        auto find_q = [&](int c) -> ppp {
          auto qi = std::lower_bound(br.begin(), br.end(), pii(c, -1));

          if (qi != br.end()) {
            if (qi->first == c) {
              if (qi == br.end() - 1) return ppp(*qi, pii(-1, -1));
              return ppp(*qi, *(qi + 1));
            }
            return ppp(*qi, *qi);
          }
          return ppp(pii(-1, -1), pii(-1, -1));
        };

        for (u32 k = 0; k < events.size(); k++) {
          int cur = events[k];
          auto [pe, pl] = find_p(cur);
          auto [qe, qg] = find_q(cur);

          if (pl.first != -1 && qe.first != -1 && 
              pl.second < qe.second) {
            work(pl.second, qe.second, cur, cur);
          }
          if (pe.first != -1 && qg.first != -1 &&
              pe.second < qg.second) {
            work(pe.second, qg.second, cur, cur);
          }

          if (k + 1 < events.size()) {
            int nxt = events[k + 1];
            if (cur + 1 < nxt) {
              auto [pe, genshin_impact] = find_p(cur + 1);
              auto [qe, wuthering_waves] = find_q(cur + 1);

              if (pe.first != -1 && qe.first != -1 &&
                  pe.second < qe.second) {
                work(pe.second, qe.second, cur + 1, nxt - 1);
              }
            }
          }
        }
      }
    }

    i = j;
  }
  
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (i) d[i][j] += d[i - 1][j];
      if (j) d[i][j] += d[i][j - 1];
      if (i && j) d[i][j] -= d[i - 1][j - 1];
      std::cout << (d[i][j] > 0 ? 1 : 0);
    }
    std::cout << "\n";
  }
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}

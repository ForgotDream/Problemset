/**
 * @file    
 * @author  ForgotDream
 * @brief   
 * @date    2023-09-05
 */
#include <iostream>
#include <string>

using i64 = long long;

constexpr int N = 105, K = 1050;
int n, k;
struct Weapon {
  std::string name, typ;
  int atk, def, res, siz;
  void input() { std::cin >> name >> typ >> atk >> def >> res >> siz; }
} w[N];
int wcnt[3];
Weapon wea[N], arm[N], orb[N];
struct Resident {
  std::string name, typ, home;
  int bonus;
  void input() { std::cin >> name >> typ >> bonus >> home; }
} r[K];
int rcnt[3];
Resident gla[N], sen[N], phy[N];
void solve() {
  std::cin >> n;
  for (int i = 1; i <= n; i++) {
    w[i].input();
    if (w[i].typ == "weapon") wea[++wcnt[0]] = w[i];
    else if (w[i].typ == "armor") arm[++wcnt[1]] = w[i];
    else orb[++wcnt[2]] = w[i];
  }
  std::cin >> k;
  for (int i = 1; i <= k; i++) {
    r[i].input();
    if (r[i].typ == "gladiator") gla[++rcnt[0]] = r[i];
    else if (r[i].typ == "sentry") sen[++rcnt[1]] = r[i];
    else phy[++rcnt[2]] = r[i];
  }
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
#include <iostream>
#include <cstring>
#include <vector>

using namespace std;
using i64 = long long;

static const int N = 20;
static const i64 INF = 0x3f3f3f3f3f3f3f3f;
int n, k;
i64 ans;
struct Mail {
  int x, y, cnt;
} mail[N];
i64 f[1 << N];
int g[1 << N][N][2];

int main() {
  freopen("envelope.in", "r", stdin);
  freopen("envelope.out", "w", stdout);
  
  ios::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);
  
  cin >> n >> k;
  for (int i = 1; i <= n; i++) {
    cin >> mail[i].x >> mail[i].y >> mail[i].cnt;
  }
  
  if (k == n) {
    cout << 0 << '\n';
  } else if (k == 1) {
    int maxX = 0, maxY = 0;
    for (int i = 1; i <= n; i++) {
      maxX = max(maxX, mail[i].x);
      maxY = max(maxY, mail[i].y);
    }
    
    for (int i = 1; i <= n; i++) {
      ans += mail[i].cnt * (i64) (maxX * maxY - mail[i].x * mail[i].y);
    }
    
    cout << ans << '\n';
  } else {
    memset(f, 0x3f, sizeof(f));
    cout << "I'm sorry, but I'm too weak to solve this difficult problem.\nI got the flu last night, please forgive me!" 
         << '\n';
  }
  
  return 0;
}

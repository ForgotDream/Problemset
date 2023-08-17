#include <iostream>
  
using namespace std;
using i64 = long long;
  
static const int N = 1e5 + 50;
int n, q, x, y;
struct Bird {
  int x1, x2, y1, y2;
} bird[N];

int myAbs(int u) {
  return u >= 0 ? u : -u;
}

void convert(int i) {
  int x1 = bird[i].x1, y1 = bird[i].y1, x2 = bird[i].x2, y2 = bird[i].y2;
  if (x1 > x2) {
    swap(x1, x2);
    swap(y1, y2);
  }
  if (y1 > y2) {
    swap(y1, y2); 
  }
  // cerr << i << ' ' << x1 << ' ' << y1 << ' ' << x2 << ' ' << y2 << '\n';
  bird[i].x1 = x1;
  bird[i].y1 = y1;
  bird[i].x2 = x2; 
  bird[i].y2 = y2;
  return;
}

int main() {
  freopen("bird.in", "r", stdin);
  freopen("bird.out", "w", stdout);
  
  ios::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);
  
  cin >> n >> q >> x >> y;
  for (int i = 1; i <= n; i++) {
    cin >> bird[i].x1 >> bird[i].y1 >> bird[i].x2 >> bird[i].y2;
    convert(i);
  }

  /*
  for (int i = 1; i <= n; i++) {
    int x1 = bird[i].x1, y1 = bird[i].y1, x2 = bird[i].x2, y2 = bird[i].y2;
    cerr << myAbs(x - x1) + myAbs(y - y1) << ' ' 
         << myAbs(x - x2) + myAbs(y - y2) << ' ' 
         << myAbs(x - x1) + myAbs(y - y2) << ' ' 
         << myAbs(x - x2) + myAbs(y - y1) << '\n';
  }
  */
  
  for (int i = 1; i <= q; i++) {
    int u, ans = 0;
    cin >> u;
    for (int j = 1; j <= n; j++) {
      int x1 = bird[j].x1, y1 = bird[j].y1, x2 = bird[j].x2, y2 = bird[j].y2;
      if (x > x1 && x < x2 && y > y1 && y < y2) {
        if (myAbs(x - x1) + myAbs(y - y1) >= u || 
            myAbs(x - x2) + myAbs(y - y2) >= u || 
            myAbs(x - x1) + myAbs(y - y2) >= u ||
            myAbs(x - x2) + myAbs(y - y1) >= u) {
          // cerr << "1: " << j << '\n';
          ans++;
        }
      } else {
        // cerr << x << ' ' << y << ' ' << x1 << ' ' << y1 << ' ' << x2 << ' ' << y2 << '\n';
        if ((myAbs(x - x1) + myAbs(y - y1) <= u && myAbs(x - x2) + myAbs(y - y2) >= u) || 
            (myAbs(x - x1) + myAbs(y - y1) >= u && myAbs(x - x2) + myAbs(y - y2) <= u) ||
            (myAbs(x - x1) + myAbs(y - y2) <= u && myAbs(x - x2) + myAbs(y - y1) >= u) ||
            (myAbs(x - x1) + myAbs(y - y2) >= u && myAbs(x - x2) + myAbs(y - y1) <= u)) {
          // cerr << "2: " << j << '\n';
          ans++;
        } else if ((y >= y1 && y <= y2 && ((myAbs(x - x1) <= u && myAbs(x - x2) >= u) || 
                                           (myAbs(x - x2) <= u && myAbs(x - x1) >= u))) 
                   ||
                   (x >= x1 && x <= x2 && ((myAbs(y - y1) <= u && myAbs(y - y2) >= u) ||
                                           (myAbs(y - y2) <= u && myAbs(y - y1) >= u)))
                  ) {
          // cerr << "3: " << j << '\n';
          ans++;
        }
      }
    }
    cout << ans << '\n';
  }
  
  return 0;
}

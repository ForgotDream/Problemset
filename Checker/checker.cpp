#include "testlib.h"
#include <cstring>
#include <algorithm>

using i64 = long long;

int main(int argc, char* argv[]) {
  registerTestlibCmd(argc, argv);

  int x1 = inf.readInt(), x2 = inf.readInt(), y1 = inf.readInt(), y2 = inf.readInt();
  int sx = ouf.readInt(), sy = ouf.readInt();
  
  if (!ouf.eof()) {
    quitf(_wa, "Your answer is too long!");
  }

  if (sx < -1e9 || sx > 1e9 || sy < -1e9 || sy > 1e9) {
    quitf(_wa, "Your answer is out of limits.");
  } else {
    i64 dis1 = (sx - x1) * (sx - x1) + (sy - y1) * (sy - y1);
    i64 dis2 = (sx - x2) * (sx - x2) + (sy - y2) * (sy - y2);
    i64 dis3 = (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1);
    if (dis1 + dis2 == dis3 || dis1 + dis3 == dis2 || dis2 + dis3 == dis1) {
      quitf(_ok, "Your answer is correct.");
    } else {
      quitf(_wa, "Your answer is wrong.");
    }
  }

  return 0;
}
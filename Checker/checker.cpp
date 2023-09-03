#include "testlib.h"

using i64 = long long;

constexpr int N = 2e5 + 50;
int b[N], b[N];

int main(int argc, char* argv[]) {
  registerTestlibCmd(argc, argv);

  auto pans = ouf.readLong(), jans = ans.readLong();
  if (pans != jans) quitf(_wa, "Your answer is worng!");

  int n = inf.readInt(), k = inf.readInt();
  inf.readEoln();
  for (int i = 1; i <= n; i++) {
    b[i] = inf.readInt(), b[i] = inf.readInt();
    inf.readEoln();
  }

  i64 pcnt = 0, psum = 0;
  for (int i = 1; i <= n; i++) {
    auto pcur = ouf.readInt();
    ouf.readEoln();
    pcnt += pcur;
    if (pcur == 0) {
      continue;
    } else if (pcur == 1) {
      psum += b[i];
    } else if (pcur == 2) {
      psum += b[i];
    } else {
      quitf(_wa, "WTF are you outputting?");
    }
  }
  if (pcnt != k) quitf(_wa, "Your answer is wrong!");
  if (psum != jans) quitf(_wa, "Well, don't try to fool a computer!");

  quitf(_ok, "Your answer is correct");

  return 0;
}
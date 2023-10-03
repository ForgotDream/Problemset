#include "testlib.h"
#include <cmath>

using i64 = long long;
using f80 = long double;

int main(int argc, char* argv[]) {
  registerTestlibCmd(argc, argv);
  auto n = inf.readInt();
  while (n--) {
    auto pans = ouf.readDouble(), jans = ans.readDouble();
    f80 eps = 1e-3;
    if (std::fabs(pans - jans) > eps) quitf(_wa, "Your answer is wrong.\n");
  }
  quitf(_ok, "Your answer is accepted.\n");
  return 0;
}
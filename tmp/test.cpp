#include <bits/stdc++.h>
#define int long long
using namespace std;
inline int read() {
    int n = 0, m = 1;
    char c = getchar();

    while (!isdigit(c)) {
        if (c == '-')
            m = -1;

        c = getchar();
    }

    while (isdigit(c))
        n = (n << 1) + (n << 3) + c - 48, c = getchar();

    return n * m;
}
#define N 1000000
int phi[1000001], prime[1000001], tot;
bool v[1000001];
void get() {
    for (int i = 2; i <= N; i++) {
        if (!v[i])
            prime[++tot] = i, phi[i] = i - 1;

        for (int j = 1; j <= tot && prime[j]*i <= N; j++) {
            v[prime[j]*i] = 1;

            if (!(i % prime[j])) {
                phi[i * prime[j]] = phi[i] * prime[j];
                break;
            }

            phi[i * prime[j]] = phi[i] * (prime[j] - 1);
        }

        phi[i] = i - phi[i];
    }

    for (int i = 1; i <= N; i++)
        phi[i] += phi[i - 1];
}
signed main() {
    ios::sync_with_stdio(0);
    int n = read();
    get();

    for (int i = 1; i <= n; i++)
        cout << "Case " << i << ": " << phi[read()] << '\n';
    return 0;
}

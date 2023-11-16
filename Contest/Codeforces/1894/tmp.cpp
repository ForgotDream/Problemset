#include <bits/stdc++.h>

using namespace std;
using ll = long long;

constexpr int N = 2e5 + 5, mod = 998244353;
constexpr double eps = 1e-8;
#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2,popcnt,tune=native")

int a[N], b[N];

int n, m, cnt;

bool flag;

void Sakuya()
{
    cin >> n >> m;

    deque<int>q;

    for(int i = 1; i <= n; ++ i)cin >> a[i], q.push_back(a[i]);

    for(int i = 1; i <= m; ++ i)cin >> b[i];

    sort(b + 1, b + 1 + m, [&](auto x, auto y){return x > y;});

    flag = 0;

    cnt = 1;

    deque<int>qq;

    while(q.size())
    {
        while(b[cnt] > q.front() && cnt <= m)
        {
            qq.push_back(b[cnt]);
            // cout << b[cnt] << " ";
            cnt ++;
        }

        while(qq.size())
        {
            cout << qq.front() << " ";
            qq.pop_front();
        }

        cout << q.front() << " ";
        q.pop_front();
    }

    while(cnt <= m)
    {
        // cout << b[cnt] << " ";
        // cnt ++;
        qq.push_back(b[cnt]);
            // cout << b[cnt] << " ";
        cnt ++;
    }

    while(qq.size())
    {
        cout << qq.front() << " ";
        qq.pop_front();
    }

    cout << '\n';
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    for (cin >> T; T -- ; )
        Sakuya();

}
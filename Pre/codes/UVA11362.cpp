#include <cstring>
#include <iostream>
#include <string>

using namespace std;

const int M = (int)1e4 + 5;
int t, n;
bool ans;
struct Trie {
  bool exist[M], vis[M];
  int nxt[M][10], cnt = 0;

  bool insert(string a) {
    int len = a.length(), p = 0;
    bool flag = true;
    for (int i = 0; i < len; i++) {
      int c = a[i] - '0';
      if (exist[p]) flag = false;
      if (!nxt[p][c]) nxt[p][c] = ++cnt, vis[p] = true;
      p = nxt[p][c];
    }
    exist[p] = true;
    if (vis[p]) flag = false;
    return flag;
  }

  bool find(string a) {
    int len = a.length(), p = 0;
    for (int i = 0; i < len; i++) {
      int c = a[i] - '0';
      if (!nxt[p][c]) return false;
      p = nxt[p][c];
    }
    return false;
  }

  void clear() {
    cnt = 0;
    memset(nxt, 0, sizeof(nxt));
    memset(vis, 0, sizeof(vis));
    memset(exist, 0, sizeof(exist));
    return;
  }
};

int main() {
  cin >> t;
  Trie trie;
  while (t--) {
    trie.clear();
    ans = false;
    cin >> n;
    for (int i = 1; i <= n; i++) {
      string s;
      cin >> s;
      if (!trie.insert(s)) ans = true;
    }
    if (!ans)
      cout << "YES" << endl;
    else
      cout << "NO" << endl;
  }
  return 0;
}
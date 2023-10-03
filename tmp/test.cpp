#include <bits/stdc++.h>
using namespace std;
int n, k, h;
// n,k,h与题中含义一致
struct stu {
  int nxt, to;
} e[10010];
int cnt;
int head[10010];
// 以上为链式前向星存图
int b[5001];    // 每一条贪吃虫所在节点
int p[5001];    // 每个节点上为哪条贪吃虫，0表示没有贪吃虫
int c[501];     // 每一次食物出现的地方
int eat[5001];  // 每条贪吃虫吃的食物数
int t[5001];    // 占领每个节点的时间
int o[5001];    // 每个节点被占据的贪吃虫编号
int f[5001];    // 题解中第二次搜索用来记录的数组
inline void add(int x, int y)  // 建边
{
  e[++cnt].nxt = head[x];
  e[cnt].to = y;
  head[x] = cnt;
}
inline void dfs1(int now, int fa)  // 第一次搜索，求出每个节点被哪条贪吃虫占据
// now为当前搜索到的节点，fa为上一次搜索的节点，避免重复搜索
{
  int mp, mt;  // 记录占领该节点的时间与贪吃虫编号
  if (p[now])  // 该点上已有贪吃虫
  {
    mp = p[now];  // 占领的贪吃虫即为该节点上的贪吃虫
    mt = 0;       // 占领速度为0
  } else          // 否则因为要取最小值，所以设一个大的数
  {
    mp = 9999;
    mt = 9999;
  }
  for (int i = head[now]; i; i = e[i].nxt)  // 依次搜索每一个儿子
  {
    int to = e[i].to;
    if (to == fa) continue;  // 避免重复搜索
    dfs1(to, now);
    if ((t[to] + 1) < mt || ((t[to] + 1) == mt && o[to] < mp))
    // 时间更短或时间相同并且编号较小即可更新
    {
      mt = t[to] + 1;
      mp = o[to];
    }
  }
  t[now] = mt;
  o[now] = mp;
  // 保存计算后的值
}
inline void dfs2(int now, int fa)  // 第二次搜索，计算每一只贪吃虫最终落脚点
// 参数意义与dfs1一致
{
  if (o[now] != 9999)  //=9999说明没有贪吃虫来过，没必要计算
  {
    if (f[o[now]] == -1 && o[fa] != o[now])
    // 没有计算过，后面的条件是因为贪吃虫一样，那么f[o[now]]没计算过，f[o[fa]]也一定没计算过
    {  // 计算，取三种可能时间的最小值
      int mt = min(t[fa], t[now]);
      f[o[now]] = min(f[o[fa]], mt);
    }
    if (f[o[now]] != -1 && f[o[now]] == t[now])
      b[o[now]] = now;  // 计算过且时间一致，则该点为这条贪吃虫的最终落脚点
  }
  for (int i = head[now]; i; i = e[i].nxt)  // 继续搜索子节点
  {
    int to = e[i].to;
    if (to == fa) continue;  // 同理，防重
    dfs2(to, now);
  }
}
int main() {
  scanf("%d", &n);
  for (int i = 1; i < n; i++)  // 读入这棵树，并建树（边）
  {
    int x, y;
    scanf("%d%d", &x, &y);
    add(x, y);
    add(y, x);  // 建双向边
  }
  scanf("%d", &k);
  for (int i = 1; i <= k; i++)  // 记录每一条贪吃虫的位置
  {
    int x;
    scanf("%d", &x);
    p[x] = i;
    b[i] = x;  // 按照数组含义记录
  }
  scanf("%d", &h);
  for (int i = 1; i <= h; i++)  // 读入每一次食物出现的位置
  {
    scanf("%d", &c[i]);
  }
  for (int i = 1; i <= h; i++) {
    memset(t, 0, sizeof(t));
    memset(o, 0, sizeof(o));
    memset(f, -1, sizeof(f));  // 由于数组内还有上一次循环的值，因此将其初始化
    dfs1(c[i], -1);        // 搜索
    ++eat[o[c[i]]];        // 将吃到食物的贪吃虫更新
    f[o[c[i]]] = t[c[i]];  // 吃到食物的贪吃虫最终落脚点即为食物处
                           // 因此到达最终落脚点的位置即为到达食物的位置
                           // 这里也是为了下面的搜索的计算
    dfs2(c[i], -1);
    memset(
        p, 0,
        sizeof(
            p));  // 由于这一轮过后贪吃虫又有了新的位置，因此先将旧的清零，并更新
    for (int j = 1; j <= k; j++) {
      p[b[j]] = j;
    }
  }
  for (int i = 1; i <= k; i++)  // 输出答案
  {
    printf("%d %d\n", b[i], eat[i]);
  }
  return 0;
}

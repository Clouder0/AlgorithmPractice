#include <algorithm>
#include <cstdio>
#include <ctype.h>
#include <queue>
#include <vector>
using namespace std;
const int bufSize = 1e6;
inline char nc() {
#ifdef DEBUG
  return getchar();
#endif
  static char buf[bufSize], *p1 = buf, *p2 = buf;
  return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, bufSize, stdin), p1 == p2)
             ? EOF
             : *p1++;
}
inline void read(char *s) {
  static char c;
  for (; !isalpha(c); c = nc())
    ;
  for (; isalpha(c); c = nc())
    *s++ = c;
  *s = '\0';
}
template <typename T> inline T read(T &r) {
  static char c;
  static int flag;
  flag = 1, r = 0;
  for (c = nc(); !isdigit(c); c = nc())
    if (c == '-')
      flag = -1;
  for (; isdigit(c); c = nc())
    r = r * 10 + c - 48;
  return r *= flag;
}
const int maxn = 2e5 + 100, maxm = 5e5 + 100;
struct node {
  int from, to;
} E[maxm];
int T, n, m;
int fa[maxn];
int f[maxn], in[maxn];
vector<int> pre[maxn];
vector<int> V[maxn];
int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }
void unite(int a, int b) { fa[find(a)] = find(b); }
int main() {
  read(T);
  while (T--) {
    read(n), read(m);
    for (int i = 1; i <= m; ++i)
      read(E[i].from), read(E[i].to);
    for (int i = 1; i <= n; ++i)
      V[i].clear(), pre[i].clear(), fa[i] = i, in[i] = 0, f[i] = 0;
    for (int i = 1; i <= m; ++i)
      pre[E[i].to].push_back(E[i].from);
    for (int i = 1; i <= n; ++i)
      for (auto j = 0; j + 1 < pre[i].size(); ++j)
        unite(pre[i][j], pre[i][j + 1]);
    for (int i = 1; i <= m; ++i)
      V[find(E[i].from)].push_back(find(E[i].to));
    for (int i = 1; i <= m; ++i)
      ++in[find(E[i].to)];
    queue<int> q;
    if (in[find(1)] != 0) {
      // puts("1");
      goto no;
    }
    q.push(find(1));
    f[find(1)] = 1;
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      for (auto v : V[u]) {
        f[v] = max(f[v], f[u] + 1);
        --in[v];
        if (in[v] == 0)
          q.push(v);
        else if (in[v] < 0)
          goto no;
      }
    }
    for (int i = 1; i <= n; ++i)
      if (in[find(E[i].to)] != 0)
        goto no;
    puts("Yes");
    printf("1 ");
    for (int i = 2; i <= n; ++i)
      printf("%d ", f[find(i)] - f[find(pre[i][0])]);
    puts("");
    continue;
  no:
    puts("No");
  }
  return 0;
}

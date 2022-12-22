#include <algorithm>
#include <cstdio>

const int maxm = 1e6 + 100;
const int maxn = 1e6 + 100;
struct node {
  int to, next, val;
} E[maxm];
int head[maxn];
inline void add(const int &x, const int &y, const int &w) {
  static int tot = 0;
  E[++tot].next = head[x], E[tot].to = y, E[tot].val = w, head[x] = tot;
}

int n;
int fa[maxn];
int d1[maxn], d2[maxn];
int maxd;
void dfs(int u) {
  for (int p = head[u]; p; p = E[p].next) {
    int v = E[p].to;
    if (v == fa[u])
      continue;
    fa[v] = u, dfs(v);
    if (d1[v] + E[p].val > d1[u])
      d2[u] = d1[u], d1[u] = d1[v] + E[p].val;
    else if (d1[v] + E[p].val > d2[u])
      d2[u] = d1[v] + E[p].val;
  }
  maxd = std::max(maxd, d1[u] + d2[u]);
}

int main() {
  scanf("%d", &n);
  for (int i = 1, u, v, w; i < n; ++i)
    scanf("%d%d%d", &u, &v, &w), add(u, v, w), add(v, u, w);
  dfs(1);
  printf("%d\n", maxd);
  return 0;
}
#include <algorithm>
#include <cstdio>

const int maxm = 1e5 + 100;
const int maxn = 1e5 + 100;
struct node {
  int to, next;
} E[maxm];
int head[maxn], tot;
inline void add(const int &u, const int &v) {
  E[++tot].next = head[u], E[tot].to = v, head[u] = tot;
}

int n, root, maxsiz;
int fa[maxn], siz[maxn];
void init() {
  root = 0;
  for (int i = 1; i <= n; ++i)
    siz[i] = 1;
  maxsiz = 1 << 30;
}
void dfs(int u) {
  int maxs = 0;
  for (int p = head[u]; p; p = E[p].next) {
    int v = E[p].to;
    if (v == fa[u])
      continue;
    fa[v] = u, dfs(v), siz[u] += siz[v];
    maxs = std::max(maxs, siz[v]);
  }
  maxs = std::max(maxs, n - siz[u]);
  if (maxs < maxsiz)
    maxsiz = maxs, root = u;
}

int main() {
  scanf("%d", &n);
  return 0;
}
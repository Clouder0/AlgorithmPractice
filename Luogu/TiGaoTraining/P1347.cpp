#include <cstdio>
#include <algorithm>
#include <ctype.h>
using namespace std;
const int maxn = 1e5;
struct node
{
    int to,next;
}E[maxn];
int head[maxn],tot;
inline void add(const int &x,const int &y)
{
    E[++tot].next = head[x], E[tot].to = y, head[x] = tot;
}
int n, m, q[maxn], qt, qh, in[maxn], tin[maxn], f[maxn];
int toposort()
{
    qh = 1, qt = 0;
    int ans = 0;
    for (int i = 1; i <= n; ++i) tin[i] = in[i];
    for (int i = 1; i <= n; ++i) if (tin[i] == 0) q[++qt] = i, f[i] = 1; else f[i] = 0;
    while (qt >= qh)
    {
        int u = q[qh++];
        for (int p = head[u]; p; p = E[p].next)
        {
            int v = E[p].to;
            f[v] = max(f[v], f[u] + 1);
            if(--tin[v] == 0) q[++qt] = v;
        }
    }
    for (int i = 1; i <= n; ++i) ans = max(ans, f[i]);
    for (int i = 1; i <= n; ++i) if (tin[i]) return -1;
    return ans;
}
char t[30];
int main()
{
    scanf("%d %d", &n, &m);
    for (int i = 1, a, b; i <= m; ++i)
    {
        char s[4];
        scanf("%s", s + 1);
        a = s[1] - 'A' + 1, b = s[3] - 'A' + 1;
        if (s[2] == '<') add(a, b), in[b]++;
        else add(b, a), in[a]++;
        int res = toposort();
        if (res == n)
        {
            for (int j = 1; j <= n; ++j) t[f[j]] = 'A' + j - 1;
            printf("Sorted sequence determined after %d relations: %s.\n", i, t + 1);
            return 0;
        }
        else if (res == -1)
        {
            printf("Inconsistency found after %d relations.\n", i);
            return 0;
        }
    }
    puts("Sorted sequence cannot be determined.");
    return 0;
}
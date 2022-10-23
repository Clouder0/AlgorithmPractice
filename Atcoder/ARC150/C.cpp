#include <cstdio>
#include <queue>
#include <algorithm>
#include <ctype.h>
using namespace std;
const int bufSize = 1e6;
inline char nc()
{
    #ifdef DEBUG
    return getchar();
    #endif
    static char buf[bufSize], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, bufSize, stdin), p1 == p2) ? EOF : *p1++;
}
inline void read(char *s)
{
    static char c;
    for (; !isalpha(c); c = nc());
    for (; isalpha(c); c = nc()) *s++ = c;
    *s = '\0';
}
template<typename T>
inline T read(T &r)
{
    static char c;
    static int flag;
    flag = 1, r = 0;
    for (c = nc(); !isdigit(c); c = nc()) if (c == '-') flag = -1;
    for (; isdigit(c); c = nc()) r = r * 10 + c - 48;
    return r *= flag;
}
const int maxn = 1e5 + 100;
const int maxm = 4e5 + 100;
int n,m,k;
struct node
{
    int to,next;
}E[maxm];
int head[maxn];
inline void add(const int &x,const int &y)
{
    static int tot = 0;
    E[++tot].next = head[x],E[tot].to = y,head[x] = tot;
}
int A[maxn],B[maxn], d[maxn],vis[maxn];
int main()
{
    read(n), read(m), read(k);
    for (int i = 1, a, b; i <= m; ++i) read(a), read(b), add(a, b), add(b, a);
    for (int i = 1; i <= n; ++i) read(A[i]);
    for (int i = 1; i <= k; ++i) read(B[i]);
    priority_queue<pair<int, int>> q;
    for (int i = 2; i <= n; ++i) d[i] = 1 << 30;
    d[1] = (B[1] == A[1]);
    q.push({-d[1], 1});
    while (!q.empty())
    {
        int u = q.top().second;
        q.pop();
        if (vis[u]) continue;
        vis[u] = 1;
//        printf("%d %d\n",u, d[u]);
        for (int p = head[u]; p; p = E[p].next)
        {
            int v = E[p].to;
            if (d[v] > d[u] + (B[d[u] + 1] == A[v]))
            {
                d[v] = d[u] + (B[d[u] + 1] == A[v]);
                q.push({-d[v], v});
            }
        }
    }
//    printf("%d\n",d[n]);
    puts(d[n] < k ? "No" : "Yes");
    return 0;
}
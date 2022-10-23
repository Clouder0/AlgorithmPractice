#include <cstdio>
#include <algorithm>
#include <ctype.h>
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
const int maxn = 2e5 + 100;
const int maxm = 4e5 + 100;
int n,b[maxn];
long long a[maxn];
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
int in[maxn];
int q[maxn],qh,qt;
int out[maxn],cnt,out2[maxn],cnt2;
int main()
{
    read(n);
    for (int i = 1; i <= n; ++i) read(a[i]);
    for (int i = 1; i <= n; ++i) read(b[i]);
    for (int i = 1; i <= n; ++i) if(b[i] != -1) add(i,b[i]),in[b[i]]++;
    long long ans = 0;
    qh = 1;
    for (int i = 1; i <= n; ++i) if(in[i] == 0) q[++qt] = i;
    while(qt >= qh)
    {
        int u = q[qh++];
        ans += a[u];
        if(a[u] >= 0) out[++cnt] = u;
        else out2[++cnt2] = u;
        for (int p = head[u]; p; p = E[p].next)
        {
            int v = E[p].to;
            if(a[u] >= 0) a[v] += a[u];
            if(--in[v] == 0) q[++qt] = v;
        }
    }
    printf("%lld\n",ans);
    for (int i = 1; i <= cnt; ++i) printf("%d ",out[i]);
    for (int i = cnt2; i; --i) printf("%d ",out2[i]);
    return 0;
}
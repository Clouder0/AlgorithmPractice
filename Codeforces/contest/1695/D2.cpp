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
const int maxn = 4e5 + 100;
int T,n;
struct node
{
    int to, next;
} E[maxn << 1];
int head[maxn],tot;
inline void add(const int &x,const int &y)
{
    E[++tot].next = head[x],E[tot].to = y,head[x] = tot;
}
int deg[maxn];
int q[maxn], qh, qt;
int main()
{
    read(T);
    while(T--)
    {
        read(n);
        tot = 0;
        for (int i = 1; i <= n; ++i) head[i] = 0, deg[i] = 0;
        for (int i = 1, u, v; i < n; ++i) read(u), read(v), add(u, v), add(v, u), ++deg[u], ++deg[v];
        int maxx = 0, res = 0;
        if(n == 1)
        {
            puts("0");
            goto end;
        }
        for (int i = 1; i <= n; ++i) maxx = std::max(maxx,deg[i]);
        if(maxx <= 2) 
        {
            puts("1");
            goto end;
        }
        qh = 1,qt = 0;
        for (int i = 1; i <= n; ++i)
            if (deg[i] == 1)
                ++res, q[++qt] = i;
        while(qt >= qh)
        {
            int u = q[qh++];
            deg[u] = 0;
            for(int p = head[u];p;p=E[p].next)
            {
                int v = E[p].to;
                if (deg[v] >= 3)
                    deg[v] = -1, --res;
                else if(deg[v] == 2)
                    q[++qt] = v;
            }
        }
        printf("%d\n", res);
        end:;
    }
    return 0;
}
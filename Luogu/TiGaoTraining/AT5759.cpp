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
struct node
{
    int to, next;
} E[maxn << 1];
int head[maxn];
inline void add(const int& x, const int& y)
{
    static int tot = 0;
    E[++tot].next = head[x], E[tot].to = y, head[x] = tot;
}
int n, col[maxn], cnt[2], res[maxn];
void dfs(int u, int fa)
{
    cnt[col[u]]++;
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if(v == fa) continue;
        col[v] = col[u] ^ 1, dfs(v, u);
    }
}
int main()
{
    read(n);
    for (int i = 1, a, b; i < n; ++i) read(a), read(b), add(a, b), add(b, a);
    dfs(1, 1);
    int mod1 = 1, mod2 = 2, mod0 = 3;
    if(cnt[0] > n / 3 && cnt[1] > n / 3)
    {
        for (int i = 1; i <= n; ++i) 
        {
            if (col[i] == 0)
            {
                if (mod1 <= n) res[i] = mod1, mod1 += 3;
                else res[i] = mod0, mod0 += 3;
            }
            else
            {
                if (mod2 <= n) res[i] = mod2, mod2 += 3;
                else res[i] = mod0, mod0 += 3;
            }
        }
    }
    else if(cnt[0] <= n / 3)
    {
        for (int i = 1; i <= n; ++i) 
        {
            if (col[i] == 0)
            {
                if (mod0 <= n) res[i] = mod0, mod0 += 3;
            }
            else
            {
                if (mod1 <= n) res[i] = mod1, mod1 += 3;
                else if (mod2 <= n) res[i] = mod2, mod2 += 3;
                else res[i] = mod0, mod0 += 3;
            }
        }
    }
    else
    {
        for (int i = 1; i <= n; ++i) 
        {
            if (col[i] == 1)
            {
                if (mod0 <= n) res[i] = mod0, mod0 += 3;
            }
            else
            {
                if (mod1 <= n) res[i] = mod1, mod1 += 3;
                else if (mod2 <= n) res[i] = mod2, mod2 += 3;
                else res[i] = mod0, mod0 += 3;
            }
        }
    }
    for (int i = 1; i <= n; ++i) printf("%d ", res[i]);
    return 0;
}
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
const int maxn = 210;
int n,m;
int a[maxn],b[maxn];
int ans[10],tans;
void dfs(int x)
{
    if(x == 9)
    {
        bool can = 1;
        int t = 0;
        for(int i = 0;i<9;++i) t |= ans[i]<<i;
        for(int i = 1;i<=n;++i) 
        {
            bool flag = 0;
            for(int j = 1;j<=m;++j)
            {
                int now = a[i] & b[j];
                if(now & (~t)) continue;
                flag = 1;
            }
            if(!flag) {return;}
        }
        if(can) tans = std::min(t,tans);
        return;
    }
    ans[x] = 0;
    dfs(x + 1);
    ans[x] = 1;
    dfs(x + 1);
}
int main()
{
    tans = 1<<30;
    read(n),read(m);
    for (int i = 1; i <= n; ++i) read(a[i]);
    for (int i = 1; i <= m; ++i) read(b[i]);
    dfs(0);
    printf("%d\n",tans);
    return 0;
}
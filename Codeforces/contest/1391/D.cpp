#include <cstdio>
#include <algorithm>
#include <ctype.h>
const int bufSize = 1e6;
#define DEBUG
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
    for (; c != '0' && c != '1'; c = nc());
    for (; c == '0' || c == '1'; c = nc()) *s++ = c;
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
const int maxn = 1e6 + 100;
int n,m;
char s[maxn];
int a[maxn];
int f[maxn][10],ok[10][10],num[10];
int main()
{
    read(n),read(m);
    if(std::min(n,m) > 3) 
    {
        puts("-1");
        return 0;
    }
    else if(std::min(n,m) == 1) 
    {
        puts("0");
        return 0;
    }
    if(n >= m)
    {
        for (int i = 1; i <= n; ++i)
        {
            read(s + 1);
            for (int j = 1; j <= m; ++j) a[i] = (a[i] << 1) + s[j] - '0';
        }
    }
    else
    {
        for (int i = 1; i <= n; ++i) 
        {
            read(s + 1);
            for (int j = 1; j <= m; ++j) a[j] = (a[j] << 1) + s[j] - '0';
        }
    }
    if(n < m) std::swap(n,m);
    int maxx = 1 << m;
    num[1] = 1;
    for (int i = 2; i < maxx; ++i) num[i] = num[i >> 1] + (i & 1);
    if(m == 3)
    {
        for (int i = 0; i < maxx; ++i)
            for (int j = 0; j < maxx; ++j)
            {
                int num1 = num[(i & 3)] + num[(j & 3)];
                int num2 = num[(i & 6)] + num[(j & 6)];
                if ((num1 & 1) && (num2 & 1)) ok[i][j] = 1;
            }
    }
    else if(m == 2)
    {
        for (int i = 0; i < maxx; ++i)
            for (int j = 0; j < maxx; ++j)
                if ((num[i] + num[j]) & 1) ok[i][j] = 1;
    }
    for (int i = 0; i < maxx; ++i) f[1][i] = num[i ^ a[1]];
    for (int i = 2; i <= n; ++i)
    {
        for (int j = 0; j < maxx; ++j) f[i][j] = 1 << 30;
        for (int j = 0; j < maxx; ++j)
        {
            for (int k = 0; k < maxx; ++k)
            {
                if (!ok[j][k]) continue;
                int x = num[k ^ a[i]];
                f[i][k] = std::min(f[i][k], f[i - 1][j] + x);
            }
        }
    }
    int ans = 1 << 30;
    for (int i = 0; i < maxx; ++i) ans = std::min(ans, f[n][i]);
    printf("%d\n", ans);
    return 0;
}
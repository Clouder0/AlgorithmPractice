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
const int maxn = 1e3 + 100;
int T,n,m,a,b;
int w[maxn][maxn],d[maxn][maxn];
void add(int x, int y, int val)
{
    int ty = y;
    while(x <= n)
    {
        y = ty;
        while(y <= m) d[x][y] += val,y += y & -y;
        x += x & -x;
    }
}
int ask(int x,int y)
{
    int res = 0,ty = y;
    while(x > 0)
    {
        y = ty;
        while(y > 0) res += d[x][y],y -= y & -y;
        x -= x & -x;
    }
    return res;
}
void rangeadd(int a,int b,int c,int d,int val)
{
    add(a, b, val), add(a, d + 1, -val), add(c + 1, b, -val), add(c + 1, d + 1, val);
}
int main()
{
    read(T);
    while(T--)
    {
        read(n), read(m), read(a), read(b);
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= m; ++j) d[i][j] = 0;
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= m; ++j) read(w[i][j]), rangeadd(i, j, i, j, w[i][j]);
        for (int i = 1; i + a - 1 <= n; ++i)
            for (int j = 1; j + b - 1 <= m; ++j)
            {
                int val = ask(i,j);
                if(val < 0) goto fail;
                if (val > 0) rangeadd(i, j, i + a - 1, j + b - 1, -val);
            }
        for (int i = n - a + 1; i <= n; ++i)
            for (int j = m - b + 1; j <= m; ++j)
                if (ask(i, j) != 0) goto fail;
        puts("^_^");
        continue;
        fail:
        puts("QAQ");
    }
    return 0;
}
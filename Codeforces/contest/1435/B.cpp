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
const int maxn = 510;
int T,n,m;
int a[maxn][maxn],mp[maxn * maxn];
int main()
{
    read(T);
    while(T--)
    {
        read(n),read(m);
        for (int i = 1; i <= n * m; ++i) mp[i] = 0;
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= m; ++j) 
            {
                read(a[i][j]); 
                if(j == 1) mp[a[i][j]] = i;
            }
        for (int i = 1, t; i <= m; ++i)
            for (int j = 1; j <= n; ++j)
            {
                read(t);
                if(mp[t])
                {
                    for(int k = 1;k<=m;++k) printf("%d ",a[mp[t]][k]);
                    puts("");
                }
            }
    }
    return 0;
}
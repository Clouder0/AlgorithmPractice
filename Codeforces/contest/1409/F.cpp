#include <cstdio>
#include <cstring>
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
char s[maxn];
char s2[maxn],t1,t2;
int f[maxn][maxn][maxn];
int main()
{
    read(n),read(m);
    read(s + 1);
    read(s2 + 1), t1 = s2[1], t2 = s2[2];
    memset(f, ~0x3f, sizeof(f));
    if(t1 == t2)
    {
        if(s[1] == t1) f[1][0][1] = 0,f[1][1][0] = 0;
        else f[1][0][0] = 0,f[1][1][1] = 0,f[1][1][0] = 0;
        for(int i = 2;i<=n;++i)
        {
            for(int j = 0;j<=i;++j)
            {
                if(s[i] == t1) 
                {
                    for (int k = 0; k <= i; ++k) if(k) f[i][j][k] = std::max(f[i][j][k], f[i - 1][j][k-1] + k - 1);
                    for (int k = 0; k <= i; ++k) if(j) f[i][j][k] = std::max(f[i][j][k], f[i - 1][j - 1][k]);
                }
                else
                {
                    for (int k = 0; k <= i; ++k) if(j && k) f[i][j][k] = std::max(f[i][j][k], f[i - 1][j - 1][k - 1] + k - 1);
                    for (int k = 0; k <= i; ++k) f[i][j][k] = std::max(f[i][j][k], f[i - 1][j][k]);
                }
            }
        }
        int ans = -(1<<30);
        for (int j = 0; j <= m; ++j)
            for (int k = 0; k <= n; ++k) ans = std::max(ans, f[n][j][k]);
        printf("%d\n", ans);
        return 0;
    }
    int ans = -(1 << 30);
    if (s[1] == t1) f[1][0][1] = 0, f[1][1][0] = 0,f[1][1][1] = 0;
    else if(s[1] == t2) f[1][0][0] = 0,f[1][1][1] = 0,f[1][1][0] = 0;
    else f[1][0][0] = 0,f[1][1][1] = 0,f[1][1][0] = 0;
    for (int i = 2; i <= n; ++i) 
    {
        for (int j = 0; j <= i; ++j)
        {
            if(s[i] == t1)
            {
                for (int k = 0; k <= i; ++k) if(k) f[i][j][k] = std::max(f[i][j][k], f[i - 1][j][k - 1]);
                for (int k = 0; k <= i; ++k) if(j) f[i][j][k] = std::max(f[i][j][k], f[i - 1][j - 1][k] + k);
                for (int k = 0; k <= i; ++k) if(j) f[i][j][k] = std::max(f[i][j][k], f[j - 1][j - 1][k]);
            }
            else if(s[i] == t2)
            {
                for (int k = 0; k <= i; ++k)  f[i][j][k] = std::max(f[i][j][k], f[i - 1][j][k] + k);
                for (int k = 0; k <= i; ++k) if(j) f[i][j][k] = std::max(f[i][j][k], f[i - 1][j - 1][k]);
                for (int k = 0; k <= i; ++k) if (j && k) f[i][j][k] = std::max(f[i][j][k], f[i - 1][j - 1][k - 1]);
            }
            else
            {
                for(int k = 0;k<=i;++k) if(j && k) f[i][j][k] = std::max(f[i][j][k],f[i-1][j-1][k-1]);
                for(int k = 0;k<=i;++k)  f[i][j][k] = std::max(f[i][j][k],f[i-1][j][k]);
                for(int k = 0;k<=i;++k) if(j) f[i][j][k] = std::max(f[i][j][k],f[i-1][j-1][k] + k);
            }
//            for(int k = 0;k<=i;++k) printf("f %d %d %d:%d\n",i,j,k,f[i][j][k]);
        }
    }
    for (int j = 0; j <= m; ++j) for (int k = 0; k <= n; ++k) ans = std::max(ans, f[n][j][k]);
    printf("%d\n", ans);
    return 0;
}
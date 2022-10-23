#include <cstdio>
#include <algorithm>
#include <ctype.h>
inline char nc(){return getchar();}
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
const int maxn = 30;
int n;
long long a[maxn][maxn];
int in[maxn];
int X[maxn*2],Y[maxn*2],cnt;
int main()
{
    read(n);
    for (int i = 1; i <= n; ++i) 
        for(int j = 1;j<=n;++j)
            if((i % 2) == 0) a[i][j] = 1ll<<(i+j-1);
    for (int i = 1; i <= n; puts(""), ++i) for (int j = 1; j <= n; ++j) printf("%lld ", a[i][j]);
    fflush(stdout);
    int m;
    read(m);
    while(m--)
    {
        long long k;
        read(k);
        puts("1 1");
        int x = 1, y = 1;
        for(int i = 1;i<=n * 2 - 2;++i)
        {
            long long flag = k & (1ll<<(i+1));
            if(x + 1 <= n && a[x+1][y] == flag) ++x;
            else ++y;
            printf("%d %d\n",x,y);
        }
        fflush(stdout);
    }
    return 0;
}
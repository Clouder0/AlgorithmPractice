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
const int mod = 998244353;
const int maxn = 10;
struct matrix
{
    int n,m;
    long long a[maxn][maxn];
    matrix()
    {
        for(int i = 0;i<=4;++i) for(int j = 0;j<=4;++j) a[i][j] = 0;
    }
    matrix operator*(const matrix b)
    {
        matrix res;
        res.n = n,res.m = b.m;
        for(int i = 1;i<=n;++i)
            for(int j = 1;j<=m;++j)
                for (int k = 1; k <= b.m; ++k) res.a[i][k] = (res.a[i][k] + a[i][j] * b.a[j][k]) % mod;
        return res;
    }
};
long long k;
int main()
{
    read(k);
    matrix A,S,X;
    A.n = A.m = 3;
    A.a[1][2] = 1,A.a[1][3] = 1,A.a[2][1] = 1,A.a[2][2] = 1,A.a[3][3] = 1;
    X.n = X.m = 3;
    for(int i = 1;i<=3;++i) X.a[i][i] = 1;
    S.n = 1,S.m = 3;
    S.a[1][1] = 1,S.a[1][2] = 1,S.a[1][3] = 0;
    while(k)
    {
        if(k & 1) X = X * A;
        A = A * A;
        k >>= 1;
    }
    S = S * X;
//    printf("%lld %lld %lld",S.a[1][1],S.a[1][2],S.a[1][3]);
    printf("%lld\n",(S.a[1][1] + S.a[1][3]) % mod);
    return 0;
}
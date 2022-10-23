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
const int maxn = 1100,maxm = 210;
const int mod = 1e9 + 7;
int n,m,K;
int f[2][maxm][maxm][2];
char A[maxn],B[maxm];
inline int add(int x,int y)
{
    int res = x + y;
    if(res >= mod) return res - mod;
    return res;
}
int main()
{
    read(n), read(m), read(K), read(A + 1), read(B + 1);
    int now = 0,last = 1;
    f[last][0][0][0] = 1;
    for (int i = 1; i <= n; ++i) 
    {
        f[now][0][0][0] = 1;
        for (int j = 1; j <= m; ++j)
            for (int k = 1; k <= K; ++k)
            {
                f[now][j][k][0] = add(f[last][j][k][0], f[last][j][k][1]);
                f[now][j][k][1] = 0;
                if (A[i] == B[j])
                {
                    f[now][j][k][1] = add(f[now][j][k][1], f[last][j - 1][k - 1][0]);
                    f[now][j][k][1] = add(f[now][j][k][1], f[last][j - 1][k - 1][1]);
                    f[now][j][k][1] = add(f[now][j][k][1], f[last][j - 1][k][1]);
                }
            }
        now ^= 1,last ^= 1;
    }
    printf("%d\n",add(f[last][m][K][1],f[last][m][K][0]));
    return 0;
}
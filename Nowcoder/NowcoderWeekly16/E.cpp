#include <cstdio>
#include <cstring>
#include <algorithm>
#include <ctype.h>
const int maxn = 4e3 + 100;
int n;
int wnum,bnum;
char s[10];
int f[maxn][maxn];//前i个，白色前j个
int id[maxn],col[maxn];
int wpos[maxn],bpos[maxn];
int wcnt[maxn][maxn],bcnt[maxn][maxn];
inline int getw(int l,int r,int x){return wcnt[r][x] - wcnt[l - 1][x];}
inline int getb(int l,int r,int x){return bcnt[r][x] - bcnt[l - 1][x];}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n * 2; ++i)
    {
        scanf("%s", s + 1), scanf("%d", id + i);
        col[i] = (s[1] == 'B');
        if(col[i]) bpos[id[i]] = i;
        else wpos[id[i]] = i;
    }
    for(int i = 1;i<=2*n;++i) 
    {
        if (col[i] == 0) for (int j = id[i]; j <= n; ++j) wcnt[i][j]++;
        else for (int j = id[i]; j <= n; ++j) bcnt[i][j]++;
        for (int j = 1; j <= n; ++j) wcnt[i][j] += wcnt[i - 1][j], bcnt[i][j] += bcnt[i - 1][j];
    }
    memset(f, 0x3f, sizeof(f));
    f[0][0] = 0;
    for (int i = 1; i <= 2 * n; ++i)
    {
        for (int j = 0; j <= n && j <= i; ++j)
        {
            int bl = i - j;
            if (j <= i - 1)
            {
                //choose black to fill i
                int bp = bpos[bl];
                f[i][j] = f[i - 1][j] + bp - i + getw(bp + 1, 2 * n, j) + getb(bp + 1, 2 * n, bl - 1);
            }
            if (j)
            {
                //choose white to fill i
                int wp = wpos[j];
                f[i][j] = std::min(f[i][j], f[i - 1][j - 1] + wp - i + getw(wp + 1, 2 * n, j - 1) + getb(wp + 1, 2 * n, bl));
            }
        }
    }
    printf("%d\n",f[2*n][n]);
    return 0;
}
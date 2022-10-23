#include <cstdio>
const int maxn = 1100;
const int mod = 19650827;
int n,h[maxn],f[maxn][maxn][2];
inline int add(int a,int b)
{
    int res = a + b;
    if(res >= mod) res -= mod;
    return res;
}
int main()
{
    scanf("%d",&n);
    if(n == 1) {puts("1"); return 0;}
    for (int i = 1; i <= n; ++i) scanf("%d", h + i);
    for (int i = 1; i <= n; ++i) f[i][i][0] = 1;
    for (int len = 2; len <= n; ++len)
        for (int l = 1, r = l + len - 1; r <= n; ++l, ++r)
        {
            if (h[l] < h[l + 1]) f[l][r][0] = add(f[l][r][0],f[l + 1][r][0]);
            if (h[l] < h[r]) f[l][r][0] = add(f[l][r][0],f[l + 1][r][1]);
            if (h[r] > h[r - 1]) f[l][r][1] = add(f[l][r][1],f[l][r - 1][1]);
            if (h[r] > h[l]) f[l][r][1] = add(f[l][r][1],f[l][r - 1][0]);
        }
    printf("%d\n", add(f[1][n][0], f[1][n][1]));
    return 0;
}
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
const int maxn = 110;
char s[maxn];
int n,numlen[maxn],f[maxn][maxn];
inline bool check(int l,int r,int k)
{
    if((r - l + 1) % (k - l + 1)) return false;
    int p = l;
    for (int i = k + 1; i <= r; ++i)
    {
        if(s[i] != s[p]) return false;
        if(++p == k + 1) p = l;
    }
    return true;
}
int main()
{
    scanf("%s",s + 1);
    n = strlen(s + 1);
    for (int i = 1; i <= n; ++i) numlen[i] = numlen[i / 10] + 1;
    memset(f,0x3f,sizeof(f));
    for (int i = 1; i <= n; ++i) f[i][i] = 1;
    for (int len = 2; len <= n; ++len)
        for (int l = 1, r = l + len - 1; r <= n; ++l, ++r)
        {
            for (int k = l; k < r; ++k)
            {
                f[l][r] = min(f[l][r],f[l][k] + f[k + 1][r]);
                if(check(l,r,k)) f[l][r] = min(f[l][r],2 + numlen[len / (k - l + 1)] + f[l][k]);
            }
        }
    printf("%d\n",f[1][n]);
    return 0;
}
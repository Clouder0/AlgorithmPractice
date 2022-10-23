#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
template<typename T>void read(T &r){static char c;r=0;for(c=getchar();c>'9'||c<'0';c=getchar());for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());}
const int maxn = 1e5 + 10;
const int maxm = 21;
int n,m;
int a[maxn];
int num[maxm];
int order[maxm];
int s[maxn][maxm];
int main()
{
    read(n);
    read(m);
    for(int i = 1;i<=n;++i)
        read(a[i]),num[a[i]]++,s[i][a[i]]++;
    for(int i = 1;i<=n;++i)
        for(int j = 1;j<=m;++j)
            s[i][j] += s[i-1][j];
    for(int i = 1;i<=m;++i)
        order[i] = i;
    int ans = 1 << 30;
    do
    {
        int res = 0;
        int l = 0,r = 0;
        for(int i = 1;i<=m;++i)
        {
            l = r + 1;
            r = l + num[order[i]] - 1;
            res += num[i] - (s[r][order[i]] - s[l-1][order[i]]);
        }
        ans = min(ans,res);
    } while (next_permutation(order + 1, order + 1 + m));
    printf("%d",ans);
    return 0;
}
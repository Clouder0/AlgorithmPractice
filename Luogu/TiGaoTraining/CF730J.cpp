#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 110;
int n;
struct node
{
    int a,b;
}A[maxn];
bool cmp(const node &a,const node &b){return a.b > b.b;}
int f[maxn][maxn * maxn];
int main()
{
    scanf("%d",&n);
    int watersum = 0;
    for (int i = 1; i <= n; ++i) scanf("%d",&A[i].a),watersum += A[i].a;
    for (int i = 1; i <= n; ++i) scanf("%d",&A[i].b);
    sort(A + 1, A + 1 + n,cmp);
    int bottlesum = 0, k;
    for (int i = 1; i <= n; ++i)
    {
        bottlesum += A[i].b;
        if (bottlesum >= watersum) { k = i; break; }
    }
    printf("%d ",k);
    memset(f,~0x3f,sizeof(f));
    f[0][0] = 0;
    for (int i = 1; i <= n; ++i)
        for (int j = bottlesum; j >= A[i].b; --j)
            for (int p = 1; p <= k; ++p) f[p][j] = max(f[p][j], f[p - 1][j - A[i].b] + A[i].a);
    int ans = 0;
    for (int i = watersum; i <= bottlesum; ++i) ans = max(ans,f[k][i]);
    printf("%d\n",watersum - ans);
    return 0;
}
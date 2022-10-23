
#include <cstdio>
#include <algorithm>
using namespace std;
#define ll long long
const int maxn = 110;
const int mod = 1e9 + 7;
int T, h, w, m, n;
int X[110], Y[110], xcnt, ycnt;
int X1[maxn],Y1[maxn],X2[maxn],Y2[maxn],V[maxn];
inline ll fastpow(ll x,ll k)
{
    ll res = 1;
    for (; k; x = (x * x) % mod, k >>= 1) if (k & 1) res = (res * x) % mod;
    return res;
}
int minn[110][110];
int popcount[1<<11];
int main()
{
    scanf("%d",&T);
    for (int i = 1; i < (1<<11); ++i) popcount[i] = popcount[i>>1] + (i & 1);
    while(T--)
    {
        scanf("%d %d %d %d",&h,&w,&m,&n);
        for (int i = 1; i <= n; ++i) scanf("%d %d %d %d %d", X1 + i, Y1 + i, X2 + i, Y2 + i, V + i),X2[i]++,Y2[i]++;
        xcnt = ycnt = 0;
        for (int i = 1; i <= n; ++i) X[++xcnt] = X1[i], X[++xcnt] = X2[i], Y[++ycnt] = Y1[i], Y[++ycnt] = Y2[i];
        X[++xcnt] = 1, Y[++ycnt] = 1, X[++xcnt] = h + 1, Y[++ycnt] = w + 1;
        sort(X + 1, X + 1 + xcnt), xcnt = unique(X + 1, X + 1 + xcnt) - X - 1;
        sort(Y + 1, Y + 1 + ycnt), ycnt = unique(Y + 1, Y + 1 + ycnt) - Y - 1;
        for (int i = 1; i <= n; ++i) X1[i] = lower_bound(X + 1, X + 1 + xcnt, X1[i]) - X, X2[i] = lower_bound(X + 1, X + 1 + xcnt, X2[i]) - X;
        for (int i = 1; i <= n; ++i) Y1[i] = lower_bound(Y + 1, Y + 1 + ycnt, Y1[i]) - Y, Y2[i] = lower_bound(Y + 1, Y + 1 + ycnt, Y2[i]) - Y;
        long long ans = 0;
        for (int i = 0; i < (1 << n); ++i)
        {
            for (int j = 1; j < xcnt; ++j) for (int k = 1; k < ycnt; ++k) minn[j][k] = m;
            for (int j = 1; j <= n; ++j)
                for (int k = X1[j]; k < X2[j]; ++k)
                    for (int p = Y1[j]; p < Y2[j]; ++p)
                        minn[k][p] = min(minn[k][p], V[j] - (i >> (j - 1) & 1));
            int res = 1;
            for (int j = 1; j < xcnt; ++j)
                for (int k = 1; k < ycnt; ++k)
                    res = (1ll * res * fastpow(minn[j][k], (X[j + 1] - X[j]) * (Y[k + 1] - Y[k]))) % mod;
            if (popcount[i] & 1)
                ans = ((ans - res) % mod + mod) % mod;
            else ans = (ans + res) % mod;
        }
        printf("%lld\n",(ans + mod) % mod);
    }
    return 0;
}

#include <cstdio>
#include <algorithm>
const int maxn = 2e5 + 100;
int n, m, q, x[maxn], y[maxn], swp[maxn], revx[maxn], revy[maxn];
long long tx[maxn], ty[maxn];
int main()
{
    scanf("%d",&n);
    for (int i = 1; i <= n; ++i) scanf("%d %d", x + i, y + i);
    revx[0] = revy[0] = 1;
    scanf("%d", &m);
    for (int i = 1, opt, t; i <= m; ++i)
    {
        revx[i] = revx[i - 1], revy[i] = revy[i - 1], tx[i] = tx[i - 1], ty[i] = ty[i - 1], swp[i] = swp[i - 1];
        scanf("%d", &opt);
        if(opt == 1) swp[i] ^= 1,std::swap(revx[i],revy[i]),std::swap(tx[i],ty[i]),revy[i] *= -1,ty[i] *= -1;
        else if(opt == 2) swp[i] ^= 1,std::swap(revx[i],revy[i]),std::swap(tx[i],ty[i]),revx[i] *= -1,tx[i] *= -1;
        else
        {
            scanf("%d", &t);
            if(opt == 3)  revx[i] *= -1,tx[i] = 2 * t - tx[i];
            else revy[i] *= -1,ty[i] = 2 * t - ty[i];
        }
    }
    scanf("%d", &q);
    for (int i = 1, opt, t; i <= q; ++i)
    {
        scanf("%d %d", &opt, &t);
        long long xx = x[t], yy = y[t];
        if (swp[opt]) std::swap(xx, yy);
        xx *= revx[opt], yy *= revy[opt], xx += tx[opt], yy += ty[opt];
        printf("%lld %lld\n", xx, yy);
    }
    return 0;
}
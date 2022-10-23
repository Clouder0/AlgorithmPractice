#include <cstdio>
#include <algorithm>
const int maxn = 1e6 + 100;
int n, m, p, q;
int bel[maxn],r[maxn * 10];
int main()
{
    scanf("%d %d %d %d",&n,&m,&p,&q);
    for (int i = m; i; --i) 
    {
        int L = (1ll * i * p + q) % n + 1;
        int R = (1ll * i * q + p) % n + 1;
        if(L > R) std::swap(L,R);
        r[i] = R;
 		for (int j = L; j <= R; ++j)
            if (bel[j]) j = r[bel[j]]; else bel[j] = i;
    }
    for (int i = 1; i <= n; ++i) printf("%d\n",bel[i]);
    return 0;
}
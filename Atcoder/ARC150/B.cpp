#include <cstdio>
#include <algorithm>
#define int long long
int T, A, B;
inline int calc(int k)
{
    if(k <= 0) return 1ll << 62;
    int Y = (B % k == 0) ? 0 : (k - (B % k));
    int X;
    if (B - k * A + Y < 0)
        Y = A * k - B, X = 0;
    else
        X = (B + Y - k * A) / k;
//    int res = k - B % k + (B - 1) / k - A;
//    printf("calc %lld %lld %lld\n",k, X,Y);
    return X+Y;
}
signed main()
{
    scanf("%lld",&T);
    while(T--)
    {
        scanf("%lld%lld",&A,&B);
        int ans = 1ll << 60;
        for(int i = 1;i * i <= B;++i)
        {
            ans = std::min(ans, calc(i));
//            if(calc(i) == 65) printf("%lld\n",i);
            int k = B / i;
            ans = std::min(ans, calc(k));
            ans = std::min(ans, calc(k-1));
            ans = std::min(ans, calc(k+1));
        }
        printf("%lld\n", ans);
    }
    return 0;
}
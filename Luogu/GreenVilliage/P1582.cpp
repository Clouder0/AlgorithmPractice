#include <cstdio>
#define int long long
int n, k;
int num[40];
signed main()
{
    scanf("%lld%lld", &n, &k);
    num[0] = n;
    for (int i = 0; i < 35; ++i)
        num[i + 1] += num[i] >> 1, num[i] &= 1;
    int sum = 0;
    for(int i = 0; i < 35;++i) sum += num[i];
    int res = 0;
    while(sum > k) {
        for (int i = 0; i < 35; ++i)
            if (num[i])
            {
                res += (1ll << i), ++num[i];
                break;
            }
        for (int i = 0; i < 35; ++i)
            num[i + 1] += num[i] >> 1, num[i] &= 1;
        sum = 0;
        for (int i = 0; i < 35; ++i) sum += num[i];
    }
    printf("%lld\n",res);
    return 0;
}
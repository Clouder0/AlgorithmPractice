#include <cstdio>
#include <cmath>
using namespace std;
int n;
int main()
{
    scanf("%d", &n);
    //二分在哪一层
    int ll = 1, rr = (sqrt(n << 1)) + 1, mid, ans, temp;
    while (ll <= rr)
    {
        mid = (ll + rr) >> 1;
        temp = mid * (mid - 1) >> 1;
        if (n > temp)
        {
            ans = mid;
            ll = mid + 1;
        }
        else
            rr = mid - 1;
    }
    //第k层分子分母和为k+1
    int t = n - (ans * (ans - 1) >> 1);
    if (ans % 2)
    {
        printf("%d/%d", ans + 1 - t, t);
    }
    else
    {
        printf("%d/%d", t, ans + 1 - t);
    }
    return 0;
}
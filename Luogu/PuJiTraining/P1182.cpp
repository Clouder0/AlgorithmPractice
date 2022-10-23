#include <cstdio>
using namespace std;
void read(int &r)
{
    static char c;r = 0;
    for (c = getchar(); c > '9' || c < '0'; c = getchar());
    for (; c >= '0' && c <= '9'; r = (r << 1) + (r << 3) + (c ^ 48), c = getchar());
}
int n, m;
int sum;
int a[100010];
inline bool check(const int &maxsum)
{
    int nowsum = 0, num = 1;
    for(int p = 1;p<=n;++p)
    {
        if(nowsum + a[p] <= maxsum)
            nowsum += a[p];
        else
            ++num,nowsum = a[p];
    }
    return num<=m;
}
int main()
{
    read(n);
    read(m);
    int ll = 1;
    for (int i = 1; i <= n; sum += a[i], ++i)
        read(a[i]),ll = a[i]>ll?a[i]:ll;
    int rr = sum, mid, ans;
    while (ll <= rr)
    {
        mid = (ll + rr) >> 1;
        if (check(mid))
        {
            rr = mid - 1;
            ans = mid;
        }
        else
            ll = mid + 1;
    }
    printf("%d", ans);
    return 0;
}
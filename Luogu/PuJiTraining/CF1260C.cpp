#include <cstdio>
#include <algorithm>
template <typename T>
void read(T &r)
{
    static char c;
    r = 0;
    for (c = getchar(); c > '9' || c < '0'; c = getchar());
    for (; c >= '0' && c <= '9'; r = (r << 1) + (r << 3) + (c ^ 48), c = getchar());
}
int T;
long long p1, p2, k;
long long gcd(long long x, long long y)
{
    if (x < y)
        std::swap(x, y);
    return y == 0 ? x : gcd(y, x % y);
}
int main()
{
    //freopen("color.in","r",stdin);
    //freopen("color.out","w",stdout);
    read(T);
    while (T--)
    {
        read(p1);
        read(p2);
        read(k);
        if (p1 > p2)
            std::swap(p1, p2);
        int gc = gcd(p1, p2);
        if(k == 1)
        {
            puts("REBEL");
            goto end;
        }
        p1 /= gc;
        p2 /= gc;
        if (p1 * (k - 1) + 1 < p2)
            puts("REBEL");
        else
            puts("OBEY");
        end:;
    }
    return 0;
}
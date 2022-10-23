#include <cstdio>
#include <cstring>
using namespace std;
template <typename T>
void read(T &r)
{
    static char c;
    r = 0;
    for (c = getchar(); c > '9' || c < '0'; c = getchar())
        ;
    for (; c >= '0' && c <= '9'; r = (r << 1) + (r << 3) + (c ^ 48), c = getchar())
        ;
}
int q;
long long b, l, r;
int num[10000];
long long f[12][70][1 << 11];
long long dfs(int pos, int lead, int up, int status)
{
    if (!pos)
        return !status;
    if (f[b][pos][status] != -1 && !lead && !up)
        return f[b][pos][status];
    int maxx = up ? num[pos] : b - 1;
    long long ans = 0;
    for (int i = 0; i <= maxx; ++i)
        ans += dfs(pos - 1, !i && lead, (i == maxx) && up, (lead && !i) ? status : status ^ (1 << i));
    if (!lead && !up)
        f[b][pos][status] = ans;
    return ans;
}
inline long long solve(long long x)
{
    int p = 0;
    while (x)
    {
        num[++p] = x % b;
        x /= b;
    }
    return dfs(p, true, true, 0);
}
int main()
{
    read(q);
    memset(f, -1, sizeof(f));
    while (q--)
    {
        read(b);
        read(l);
        read(r);
        printf("%lld\n", solve(r) - solve(l - 1));
    }
    return 0;
}
#include <cstdio>
#include <algorithm>
using namespace std;
void read(int &r)
{
    static char c;
    r = 0;
    for (c = getchar(); c > '9' || c < '0'; c = getchar())
        ;
    for (; c >= '0' && c <= '9'; r = (r << 1) + (r << 3) + (c ^ 48), c = getchar())
        ;
}
int m, n, k;
int all[21][21];
struct pe
{
    int x, y, num;
    bool operator<(const pe &b) const
    {
        return this->num > b.num;
    }
} pes[401];
int cnt;
int main()
{
    read(n);
    read(m);
    read(k);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
        {
            read(all[i][j]);
            if (all[i][j])
                pes[++cnt] = (pe){j, i, all[i][j]};
        }
    sort(pes + 1, pes + 1 + cnt);
    int T = 0, dx, dy, ans = 0;
    if (cnt == 0)
    {
        printf("0");
        return 0;
    }
    T += pes[1].y + 1;
    if (T + pes[1].y > k)
    {
        printf("0");
        return 0;
    }
    ans += pes[1].num;
    for (int i = 2; i <= cnt; ++i)
    {
        dx = abs(pes[i].x - pes[i - 1].x);
        dy = abs(pes[i].y - pes[i - 1].y);
        if (dx + dy + T + pes[i].y + 1 > k)
            break;
        T += dx + dy + 1;
        ans += pes[i].num;
    }
    printf("%d", ans);
    return 0;
}
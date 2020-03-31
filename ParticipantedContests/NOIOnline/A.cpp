#include <cstdio>
#include <algorithm>
using namespace std;
template <typename T>
inline T _min(const T &a, const T &b) { return a < b ? a : b; }
template <typename T>
inline T read(T &r)
{
    static char c;
    r = 0;
    for (c = getchar(); c > '9' || c < '0'; c = getchar());
    for (; c >= '0' && c <= '9'; r = (r << 1) + (r << 3) + (c ^ 48), c = getchar());
    return r;
}
const int maxn = 1e5 + 100;
struct opt
{
    int t, u, v;
} E[maxn];
bool cmp(const opt &a, const opt &b)
{
    if (a.u == b.u)
        return a.v < b.v;
    return a.u < b.u;
}
int T, n, m;
int a[maxn], b[maxn];
int main()
{
    freopen("sequence.in","r",stdin);
    freopen("sequence.out","w",stdout)
    read(T);
    while (T--)
    {
        read(n);
        read(m);
        for (int i = 1; i <= n; ++i)
            read(a[i]);
        for (int i = 1; i <= n; ++i)
            read(b[i]);
        for (int i = 1; i <= m; ++i)
            read(E[i].t), read(E[i].u), read(E[i].v);
        if (n == 2 && m == 1)
        {
            if (E[1].t == 1)
            {
                if (b[1] - a[1] == b[2] - a[2])
                    puts("YES");
                else
                    puts("NO");
                goto end;
            }
            else if (E[1].t == 2)
            {
                if (b[1] - a[1] == a[2] - b[2])
                    puts("YES");
                else
                    puts("NO");
                goto end;
            }
        }
        else if (n == 2 && m != 1)
        {
            b[1] -= a[1];
            b[2] -= a[2];
            int minn = _min(b[1], b[2]);
            b[1] -= minn;
            b[2] -= minn;
            if (b[1] == 0)
            {
                if (b[2] % 2 == 0)
                    puts("YES");
                else
                    puts("NO");
            }
            else
            {
                if (b[1] % 2 == 0)
                    puts("YES");
                else
                    puts("NO");
            }
            goto end;
        }
        else
        {
            int flag = 0;
            for (int i = 1; i <= m; ++i)
                if (E[i].t == 1)
                    flag = 1;
            if (flag == 0)
            {
                int sum = 0;
                for (int i = 1; i <= n; ++i)
                    b[i] -= a[i], sum += b[i];
                if (sum != 0)
                {
                    puts("NO");
                    goto end;
                }
                int con = 0, cnt = 0;
                sort(E + 1, E + 1 + m, cmp);
                while (1)
                {
                    ++cnt;
                    if (cnt >= 20)
                        break;
                    con = 0;
                    for (int i = 1; i <= n; ++i)
                        if (b[i])
                            con = 1;
                    if (con == 0)
                        break;
                    for (int i = 1; i <= m; ++i)
                    {
                        if (b[E[i].u] != 0 && b[E[i].v] != 0)
                        {
                            if (b[E[i].u] < b[E[i].v])
                            {
                                b[E[i].v] += b[E[i].u];
                                b[E[i].u] -= b[E[i].u];
                            }
                            else
                            {
                                b[E[i].v] -= b[E[i].u];
                                b[E[i].u] += b[E[i].u];
                            }
                        }
                        else if (b[E[i].v] != 0)
                        {
                        }
                    }
                }
                int can = 1;
                for (int i = 1; i <= n; ++i)
                    if (b[i])
                        can = 0;
                if (can)
                    puts("YES");
                else
                    puts("NO");
                goto end;
            }
            else
            {
                int sum = 0;
                for (int i = 1; i <= n; ++i)
                    b[i] -= a[i], sum += b[i];
                if (sum % 2 == 0)
                    puts("YES");
                else
                    puts("NO");
                goto end;
            }
        }
    end:;
    }
    return 0;
}

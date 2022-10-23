#include <cstdio>
#include <algorithm>
using namespace std;
template <typename T>
inline void read(T &r)
{
    static char c;
    r = 0;
    for (c = getchar(); c > '9' || c < '0'; c = getchar());
    for (; c >= '0' && c <= '9'; r = (r << 1) + (r << 3) + (c ^ 48), c = getchar());
}
const int maxn = 1e5 + 10;
struct node
{
    int root, ls, rs;
    int val, dis;
} a[maxn];
int n, m;
int merge(int x, int y)
{
    if (!x || !y)
        return x + y;
    if (a[x].val > a[y].val || (a[x].val == a[y].val && x > y))
        std::swap(x, y);
    a[x].rs = merge(a[x].rs, y);
    if (a[a[x].ls].dis < a[a[x].rs].dis)
        std::swap(a[x].ls, a[x].rs);
    a[a[x].ls].root = a[a[x].rs].root = x;
    a[x].dis = a[a[x].rs].dis + 1;
    return x;
}
inline void pop(int x)
{
    a[x].val = -1;
    a[a[x].ls].root = a[x].ls;
    a[a[x].rs].root = a[x].rs;
    a[x].root = merge(a[x].ls, a[x].rs);
}
inline int getfa(int x)
{
    return a[x].root == x ? x : a[x].root = getfa(a[x].root);
}
int main()
{
    read(n);
    read(m);
    for (int i = 1; i <= n; ++i)
        read(a[i].val), a[i].root = i, a[i].ls = a[i].rs = 0, a[i].dis = 0;
    int t, x, y;
    for (int i = 1; i <= m; ++i)
    {
        read(t);
        read(x);
        if (t == 1)
        {
            read(y);
            if (a[x].val == -1 || a[y].val == -1)
                continue;
            int fx = getfa(x), fy = getfa(y);
            if (fx != fy)
                a[fx].root = a[fy].root = merge(fx, fy);
        }
        else
        {
            if (a[x].val == -1)
                puts("-1");
            else
            {
                printf("%d\n", a[getfa(x)].val);
                pop(getfa(x));
            }
        }
    }
    return 0;
}
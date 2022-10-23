#include <cstdio>
#include <algorithm>
using namespace std;
template <typename T>
void read(T &r)
{
    static char c;
    r = 0;
    for (c = getchar(); c > '9' || c < '0'; c = getchar());
    for (; c >= '0' && c <= '9'; r = (r << 1) + (r << 3) + (c ^ 48), c = getchar());
}
const int maxn = 5e4 + 100;
const int maxm = 1e5 + 100;
struct node
{
    int from,to, next, val, col;
} E[maxm];
int head[maxn];
int tot;
inline void add(const int &x, const int &y, const int &val, const int &col)
{
    E[++tot].to = y;
    E[tot].next = head[x];
    E[tot].from = x;
    E[tot].val = val;
    E[tot].col = col;
    head[x] = tot;
}
int n, m, need, xx;
bool cmp(const node &a, const node &b)
{
    if(a.val == b.val)
        return a.col < b.col;
    return a.val < b.val;
}
int fa[maxn];
inline int find(const int &x)
{
    return fa[x] == x ? x : fa[x] = find(fa[x]);
}
int sum,asum;
inline int check()
{
    sum = 0;
    int white = 0;
    for(int i = 1;i<=tot;++i)
        E[i].val += !E[i].col?xx:0;
    sort(E + 1, E + 1 + tot, cmp);
    for(int i = 1;i<=n;++i)
        fa[i] = i;
    for(int i = 1;i <= tot;++i)
    {
        int u = find(E[i].from);
        int v = find(E[i].to);
        if(u != v)
        {
            white += !E[i].col;
            sum += E[i].val;
            fa[u] = v;
        }
    }
    for(int i = 1;i<=tot;++i)
        E[i].val -= !E[i].col?xx:0;
    return white;
}
int main()
{
    read(n);
    read(m);
    read(need);
    int a, b, c, d;
    for (int i = 1; i <= m; ++i)
    {
        read(a);
        read(b);
        read(c);
        read(d);
        add(a + 1, b + 1, c, d);
    }
    int l = -101, r = 101, mid, ans;
    while (l <= r)
    {
        mid = l + r >> 1;
        xx = mid;
        if (check() >= need)
            asum = sum,ans = mid, l = mid + 1;
        else
            r = mid - 1;
    }
    printf("%d",asum - need * ans);
    return 0;
}

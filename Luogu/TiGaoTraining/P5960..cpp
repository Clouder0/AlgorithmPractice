#include <cstdio>
#include <queue>
#include <memory.h>
using namespace std;
const int maxn = 5e4 + 100;
template <typename T>
void read(T &r)
{
    static char c;
    static int flag;
    flag = 1, r = 0;
    for (c = getchar(); c > '9' || c < '0'; c = getchar()) if (c == '-') flag = -1;
    for (; c >= '0' && c <= '9'; r = (r << 1) + (r << 3) + (c ^ 48), c = getchar());
    r *= flag;
}
struct node
{
    int to, next, val;
} E[maxn];
int head[maxn];
inline void add(const int &x, const int &y, const int &val)
{
    static int tot = 0;
    E[++tot] = (node){y, head[x], val}, head[x] = tot;
}
int n, m;
int dis[maxn];
int pre[maxn];
bool inq[maxn];
queue<int> q;
inline bool spfa()
{
    memset(dis, 0x3f, sizeof(dis));
    dis[0] = 0;
    q.push(0);
    int u, v;
    while (!q.empty())
    {
        u = q.front();
        q.pop();
        inq[u] = 0;
        if (pre[u] > n + 2)
            return false;
        for (int p = head[u]; p; p = E[p].next)
        {
            v = E[p].to;
            if (dis[v] > dis[u] + E[p].val)
            {
                dis[v] = dis[u] + E[p].val;
                pre[v] = pre[u] + 1;
                if (!inq[v])
                    q.push(v), inq[v] = 1;
            }
        }
    }
    return true;
}
int main()
{
    read(n);
    read(m);
    for (int i = 1; i <= n; ++i)
        add(0, i, 0);
    int a, b, c;
    while (m--)
    {
        read(a);
        read(b);
        read(c);
        add(b, a, c);
    }
    if (spfa())
        for (int i = 1; i <= n; ++i)
            printf("%d ", dis[i]);
    else
        puts("NO");
    return 0;
}
#include <cstdio>
#include <map>
#include <queue>
#include <vector>
template <typename T>
void read(T &r)
{
    static char c;
    r = 0;
    for (c = getchar(); c > '9' || c < '0'; c = getchar());
    for (; c >= '0' && c <= '9'; r = (r << 1) + (r << 3) + (c ^ 48), c = getchar());
}
const int maxn = 1e5 + 100;
const int maxq = 5e5 + 100;
int T, n, m;
int costtime[maxn], used[maxn];
int opt, id, l, r;
inline int lowbit(const int &x) { return x & -x; }
struct Bit
{
    int sum[maxn], vis[maxn], cnt;
    inline void clear() { ++cnt; }
    inline void check(int x) {if (vis[x] != cnt) vis[x] = cnt, sum[x] = 0;}
    inline void add(int x, int k){while (x <= n) check(x), sum[x] += k, x += lowbit(x);}
    inline int ask(int x)
    {
        int res = 0;
        while (x > 0) check(x), res += sum[x], x -= lowbit(x);
        return res;
    }
};
namespace Seg
{
    Bit A, B;
    inline void add(int x, int k)
    {
        A.add(x, k), A.add(x + 1, -k);
        B.add(x, k * x), B.add(x + 1, -k * (x + 1));
    }
    inline int ask(int x) { return A.ask(x) * (x + 1) - B.ask(x); }
    inline int ask(int l, int r) { return ask(r) - ask(l - 1); }
    inline void clear() { A.clear(), B.clear(); }
} // namespace Seg
struct node
{
    int id, t;
};
std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int> >, std::greater<std::pair<int, int> > > all;
std::priority_queue<int, std::vector<int>, std::greater<int> > cooked, A[maxn];
inline void update(int t)
{
    while (!all.empty())
    {
        int ft = all.top().first, id = all.top().second;
        if (ft > t) break;
        all.pop();
        Seg::add(id, 1);
        cooked.push(id);
    }
}
int main()
{
    read(T);
    while (T--)
    {
        read(n);
        Seg::clear();
        while (!all.empty()) all.pop();
        while (!cooked.empty()) cooked.pop();
        for (int i = 1; i <= n; ++i) while (!A[i].empty()) A[i].pop();
        for (int i = 1; i <= n; ++i) used[i] = 0;
        for (int i = 1; i <= n; ++i) read(costtime[i]);
        read(m);
        while (m--)
        {
            int t;
            read(t), read(opt);
            update(t);
            if (opt == 0)
            {
                read(id);
                int ft = t + costtime[id];
                A[id].push(ft), all.push(std::make_pair(ft, id));
            }
            else if (opt == 1)
            {
                while (!cooked.empty() && used[cooked.top()]) --used[cooked.top()], cooked.pop();
                if (cooked.empty()) puts("Yazid is angry.");
                else
                {
                    int id = cooked.top();
                    cooked.pop();
                    A[id].pop();
                    Seg::add(id, -1);
                    printf("%d\n", id);
                }
            }
            else if (opt == 2)
            {
                read(id);
                if (A[id].empty()) puts("YJQQQAQ is angry.");
                else
                {
                    int ft = A[id].top();
                    if (ft <= t) puts("Succeeded!"), A[id].pop(), used[id]++, Seg::add(id, -1);
                    else printf("%d\n", ft - t);
                }
            }
            else if (opt == 3)
            {
                read(l), read(r);
                printf("%d\n", Seg::ask(l, r));
            }
        }
    }
    return 0;
}
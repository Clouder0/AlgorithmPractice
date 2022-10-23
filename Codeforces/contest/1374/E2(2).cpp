#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;
template <typename T>
void read(T &r)
{
    static char c;
    r = 0;
    for (c = getchar(); c > '9' || c < '0'; c = getchar());
    for (; c >= '0' && c <= '9'; r = (r << 1) + (r << 3) + (c ^ 48), c = getchar());
}
const int maxn = 2e5 + 100;
int n, m, k;
struct node
{
    int t, id;
    bool operator<(const node &b) const { return t == b.t ? id < b.id : t < b.t; }
    bool operator>(const node &b) const { return t == b.t ? id > b.id : t > b.t; }
} A[4][maxn];
int num[4];
long long sums[4][maxn];
inline void init()
{
    read(n), read(m), read(k);
    for (int i = 1; i <= n; ++i)
    {
        int t, a, b, p;
        read(t), read(a), read(b), p = (a << 1) + b;
        A[p][++num[p]].id = i, A[p][num[p]].t = t;
    }
    for (int i = 0; i < 4; ++i) sort(A[i] + 1, A[i] + 1 + num[i]);
    for (int i = 0; i < 4; ++i) for (int j = 1; j <= num[i]; ++j) sums[i][j] = sums[i][j - 1] + A[i][j].t;
}
priority_queue<node, vector<node>, greater<node> > all;
priority_queue<node, vector<node>, less<node> > choose;
int vis[maxn];
int sum, need, start, ansp = -1;
long long ans = 1ll<<60;
inline void updateChoose()
{
    if (need < 0) need = 0;
    while (choose.size() > need) sum -= choose.top().t, all.push(choose.top()), choose.pop();
    while (choose.size() < need && !all.empty()) sum += all.top().t, choose.push(all.top()), all.pop();
    while (!choose.empty() && !all.empty() && choose.top().t > all.top().t)
    {
        sum -= choose.top().t, sum += all.top().t;
        all.push(choose.top()), choose.pop();
        choose.push(all.top()), all.pop();
    }
}
inline void updateRange(int i)
{
    if (k - i >= 0)
    {
        need = m - k * 2 + i;
        if (k - i + 1 <= num[1] && !vis[A[1][k - i + 1].id]) all.push(A[1][k - i + 1]), vis[A[1][k - i + 1].id] = 1;
        if (k - i + 1 <= num[2] && !vis[A[2][k - i + 1].id]) all.push(A[2][k - i + 1]), vis[A[2][k - i + 1].id] = 1;
    }
    else need = m - i;
}
inline void clear()
{
    while (!all.empty()) vis[all.top().id] = 0, all.pop();
    while (!choose.empty()) vis[choose.top().id] = 0, choose.pop();
}
inline void initPush()
{
    for (int i = 0; i < 3; ++i) 
        for (int j = num[i]; j > (i == 0 ? 0 : k - start); --j) 
            if (!vis[A[i][j].id]) all.push(A[i][j]), vis[A[i][j].id] = 1;
}
int main()
{
    init();
    while (start <= num[3] && (k - start > num[1] || k - start > num[2] || m - start - (k - start) * 2 < 0)) ++start;
    if (start == num[3] + 1)
    {
        puts("-1");
        return 0;
    }
    initPush();
    for (int i = start; i <= num[3]; ++i)
    {
        updateRange(i), updateChoose();
        int res = sums[3][i] + sum;
        if (k - i >= 0) res += sums[1][k - i] + sums[2][k - i];
        if (res < ans && ((k - i >= 0) ? (i + 2 * (k - i) + choose.size() == m) : (i + choose.size() == m))) ans = res, ansp = i;
    }
    printf("%lld\n", ans);
    clear();
    initPush();
    for (int i = start; i <= num[3]; ++i)
    {
        updateRange(i), updateChoose();
        if (i == ansp)
        {
            for (int j = 1; j <= i; ++j) printf("%d ", A[3][j].id);
            if (k - i > 0) for (int j = 1; j <= k - i; ++j) printf("%d %d ", A[1][j].id, A[2][j].id);
            while (!choose.empty()) printf("%d ", choose.top().id), choose.pop();
            return 0;
        }
    }
    puts("-1");
    return 0;
}
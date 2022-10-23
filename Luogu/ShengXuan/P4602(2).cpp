#include <cstdio>
#include <algorithm>
#include <ctype.h>
const int bufSize = 1e6;
inline char nc()
{
    #ifdef DEBUG
    return getchar();
    #endif
    static char buf[bufSize], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, bufSize, stdin), p1 == p2) ? EOF : *p1++;
}
template<typename T>
inline T read(T &r)
{
    static char c;
    static int flag;
    flag = 1, r = 0;
    for (c = nc(); !isdigit(c); c = nc()) if (c == '-') flag = -1;
    for (; isdigit(c); c = nc()) r = r * 10 + c - 48;
    return r *= flag;
}
const int maxn = 1e5 + 100;
int n, m, ans[maxn], H[maxn], hcnt, lg[maxn];
struct juice
{
    int taste, cost, limit;
} A[maxn];
bool cmp(const juice& a, const juice& b) { return a.taste < b.taste; }
struct query
{
    int id;
    long long money, need;
} B[maxn], q1[maxn], q2[maxn];
long long costsum[maxn], limitsum[maxn];
inline void add(int cost, int limit)
{
    long long totalcost = 1ll * H[cost] * limit;
    for (; cost <= hcnt; cost += cost & -cost) costsum[cost] += totalcost, limitsum[cost] += limit;
}
void solve(int l, int r, int L, int R)
{
    if(L > R) return;
    if(l == r)
    {
        for (int i = L; i <= R; ++i) ans[B[i].id] = A[l].taste;
        return;
    }
    int mid = l + r >> 1, cnt1 = 0, cnt2 = 0;
    for (int i = mid + 1; i <= r; ++i) add(A[i].cost, A[i].limit);
    for (int i = L; i <= R; ++i)
    {
        long long nowcost = 0, nowlimit = 0;
        int p = 0;
        for (int j = lg[hcnt - p]; j >= 0; j = std::min(j - 1, lg[hcnt - p]))
        {
            if (p + (1 << j) <= hcnt && nowcost + costsum[p + (1 << j)] <= B[i].money)
            {
                nowcost += costsum[p += (1 << j)], nowlimit += limitsum[p];
                if(nowlimit >= B[i].need) { q2[++cnt2] = B[i]; goto end; }
            }
        }
        if (limitsum[p + 1] + nowlimit >= B[i].need && (B[i].need - nowlimit) * H[p + 1] <= B[i].money - nowcost) q2[++cnt2] = B[i];
        else q1[++cnt1] = B[i];
        end: ;
    }
    for (int i = 1; i <= cnt1; ++i) B[L + i - 1] = q1[i];
    for (int i = 1; i <= cnt2; ++i) B[L + cnt1 + i - 1] = q2[i];
    solve(l, mid, L, L + cnt1 - 1);
    for (int i = mid + 1; i <= r; ++i) add(A[i].cost, -A[i].limit);
    solve(mid + 1, r, L + cnt1, R);
}
signed main()
{
    read(n), read(m);
    for (int i = 2; i <= n; ++i) lg[i] = lg[i >> 1] + 1;
    for (int i = 1; i <= n; ++i) read(A[i].taste), read(A[i].cost), read(A[i].limit), H[++hcnt] = A[i].cost;
    std::sort(H + 1, H + 1 + hcnt), hcnt = std::unique(H + 1, H + 1 + hcnt) - H - 1;
    for (int i = 1; i <= n; ++i) A[i].cost = std::lower_bound(H + 1, H + 1 + hcnt, A[i].cost) - H;
    for (int i = 1; i <= m; ++i) read(B[i].money), read(B[i].need), B[i].id = i;
    std::sort(A + 1, A + 1 + n, cmp);
    solve(0, n, 1, m);
    for (int i = 1; i <= m; ++i) if (ans[i]) printf("%d\n", ans[i]); else puts("-1");
    return 0;
}
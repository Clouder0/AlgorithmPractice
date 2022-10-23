#include <cstdio>
#include <algorithm>
#include <cmath>
#include <vector>
#include <ctype.h>
const int bufSize = 2e6;
using namespace std;
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
int n, m, cnt, ANS[maxn];
struct query
{
    int opt, pos, x, t, id;
} Q[4 * maxn];
bool cmp(const query& a, const query& b) { return a.pos == b.pos ? a.t < b.t : a.pos < b.pos; }
int bel[maxn], L[maxn], R[maxn];
long long a[maxn], tag[maxn];
vector<long long> V[1000];
void make(int id)
{
    for (int i = L[id]; i <= R[id]; ++i) a[i] += tag[id];
    tag[id] = 0, V[id].clear();
    for (int i = L[id]; i <= R[id]; ++i) V[id].push_back(a[i]);
    sort(V[id].begin(), V[id].end());
}
void add(int l, int r, int k)
{
    int lp = bel[l], rp = bel[r];
    if (lp == rp)
    {
        for (int i = l; i <= r; ++i) a[i] += k;
        make(lp);
        return;
    }
    for (int i = l; i <= R[lp]; ++i) a[i] += k;
    for (int i = L[rp]; i <= r; ++i) a[i] += k;
    make(lp), make(rp);
    for (int i = lp + 1; i < rp; ++i) tag[i] += k;
}
int ask(int l, int r, int k)
{
    int lp = bel[l], rp = bel[r], res = 0;
    if (lp == rp)
    {
        for (int i = l; i <= r; ++i) res += (a[i] + tag[bel[i]] >= k);
        return res;
    }
    for (int i = l; i <= R[lp]; ++i) res += (a[i] + tag[bel[i]] >= k);
    for (int i = L[rp]; i <= r; ++i) res += (a[i] + tag[bel[i]] >= k);
    for (int i = lp + 1; i < rp; ++i) res += V[i].end() - lower_bound(V[i].begin(), V[i].end(), k - tag[i]);
    return res;
}
signed main()
{
    read(n), read(m);
    for (int i = 1, x; i <= n; ++i) 
    {
        read(x), Q[++cnt].opt = 1, Q[cnt].pos = i, Q[cnt].x = x, Q[cnt].t = 1;
        Q[++cnt].opt = 1, Q[cnt].pos = i + 1, Q[cnt].x = -x, Q[cnt].t = 1;
    }
    int qnum = 0;
    for (int i = 1, opt, l, r, x; i <= m; ++i)
    {
        read(opt), read(l);
        if (opt == 1)
        {
            read(r), read(x), Q[++cnt].opt = 1, Q[cnt].pos = l, Q[cnt].t = i + 1, Q[cnt].x = x;
            Q[++cnt].opt = 1, Q[cnt].pos = r + 1, Q[cnt].t = i + 1, Q[cnt].x = -x;
        }
        else read(x), Q[++cnt].opt = 2, Q[cnt].t = i + 1, Q[cnt].pos = l, Q[cnt].x = x, Q[cnt].id = ++qnum;
    }
    sort(Q + 1, Q + 1 + cnt, cmp);
    int len = std::max(100, (int)(std::sqrt((m + 1) / 6)));
    for (int i = 1; i <= m + 1; ++i) bel[i] = (i - 1) / len + 1, V[bel[i]].push_back(0);
    for (int i = 1; i <= m + 1; ++i)
    {
        if (L[bel[i]] == 0) L[bel[i]] = i;
        R[bel[i]] = i;
    }
    for (int i = 1; i <= cnt; ++i)
    {
        if (Q[i].opt == 1) add(Q[i].t, m + 1, Q[i].x);
        else ANS[Q[i].id] = ask(1, Q[i].t - 1, Q[i].x);
    }
    for (int i = 1; i <= qnum; ++i) printf("%d\n", ANS[i]);
    return 0;
}
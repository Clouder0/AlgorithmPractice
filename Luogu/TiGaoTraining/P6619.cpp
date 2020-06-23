#include <cstdio>
#include <algorithm>
template <typename T>
inline T min(const T &a, const T &b) { return a < b ? a : b; }
const int bufSize = 1e6;
inline char nc()
{
    static char buf[bufSize], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, bufSize, stdin), p1 == p2) ? EOF : *p1++;
}
template <typename T>
void read(T &r)
{
    static char c; r = 0;
    for (c = nc(); c > '9' || c < '0'; c = nc());
    for (; c >= '0' && c <= '9'; r = (r << 1) + (r << 3) + (c ^ 48), c = nc());
}
const int maxn = 4e6 + 100;
int n;
struct query
{
    int opt, t, x, y;
} Q[maxn];
int H[maxn], tot;
inline int lowbit(const int &x) { return x & -x; }
struct Bit
{
    long long sum[maxn];
    Bit(){ for (int i = 0; i <= tot; ++i) sum[i] = 0;} //初始化清空数组
    inline void add(int x, int k) { for (; x <= tot; x += lowbit(x)) sum[x] += k;}
    inline long long ask(int x)
    {
        long long res = 0;
        for (; x > 0; x -= lowbit(x)) res += sum[x];
        return res;
    }
};
struct Cit
{
    Bit A, B;
    inline void add(int l, int r, int k)
    {
        A.add(l, k), A.add(r + 1, -k);
        B.add(l, l * k), B.add(r + 1, -(r + 1) * k);
    }
    inline long long ask(int x) { return A.ask(x) * (x + 1) - B.ask(x); }
    inline long long ask(int l, int r) { return ask(r) - ask(l - 1); }
} A, B;
void output()
{
    int l = 1, r = tot, mid, anst = 0, ansp = 0;
    long long ans = 0;
    while (l <= r) //找到冰>火的最小温度
    {
        mid = l + r >> 1;
        if (A.ask(mid) > B.ask(mid, tot)) anst = mid, r = mid - 1;
        else l = mid + 1;
    }
    ans = min(A.ask(anst), B.ask(anst, tot)) * 2;
    ansp = anst;
    l = 1, r = tot, anst = 0;
    while (l <= r) //找到 冰<=火的最大温度
    {
        mid = l + r >> 1;
        if (A.ask(mid) <= B.ask(mid, tot)) anst = mid, l = mid + 1;
        else r = mid - 1;
    }
    long long temp = min(A.ask(anst), B.ask(anst, tot)) * 2;
    if (temp > ans || (temp == ans && anst > ansp)) ans = temp, ansp = anst;
    while (++anst <= n && min(A.ask(anst), B.ask(anst, tot)) * 2 == ans) ansp = anst;
    if (ans == 0) puts("Peace");
    else printf("%d %lld\n", H[ansp], ans);
}
int main()
{
    read(n);
    for (int i = 1; i <= n; ++i)
    {
        read(Q[i].opt);
        if (Q[i].opt == 1) read(Q[i].t), read(Q[i].x), read(Q[i].y), H[++tot] = Q[i].x;
        else read(Q[i].t);
    }
    std::sort(H + 1, H + 1 + tot);
    tot = std::unique(H + 1, H + 1 + tot) - H - 1;
    for (int i = 1; i <= n; ++i)
    {
        if (Q[i].opt == 1)
        {
            int x = std::lower_bound(H + 1, H + 1 + tot, Q[i].x) - H;
            if (Q[i].t == 0) A.add(x, x, Q[i].y);
            else B.add(x, x, Q[i].y);
        }
        else
        {
            int p = Q[i].t;
            int x = std::lower_bound(H + 1, H + 1 + tot, Q[p].x) - H;
            if (Q[p].t == 0) A.add(x, x, -Q[p].y);
            else B.add(x, x, -Q[p].y);
        }
        output();
    }
    return 0;
}
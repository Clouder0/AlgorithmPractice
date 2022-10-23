#include <cstdio>
template <typename T>
inline T min(const T &a, const T &b) { return a < b ? a : b; }
template <typename T>
inline T max(const T &a, const T &b) { return a > b ? a : b; }
template <typename T>
inline T max(const T &a, const T &b, const T &c) { return max(c, max(a, b)); }
template <typename T>
void read(T &r)
{
    static char c;
    r = 0;
    for (c = getchar(); c > '9' || c < '0'; c = getchar());
    for (; c >= '0' && c <= '9'; r = (r << 1) + (r << 3) + (c ^ 48), c = getchar());
}
const int maxn = 2e5 + 100;
int n, m;
struct node
{
    int l, r, lmax, rmax, mmax, tag, sum, len;
} A[maxn << 2];
inline void pushup(node &now, node &ls, node &rs)
{
    now.sum = ls.sum + rs.sum;
    now.lmax = ls.lmax + !ls.sum * rs.lmax;              //sum==0时全覆盖
    now.rmax = rs.rmax + !rs.sum * ls.rmax;              //全覆盖则加上另一边
    now.mmax = max(ls.mmax, rs.mmax, ls.rmax + rs.lmax); //取左半边最长、右半边最长或跨越中界最长
}
inline void pushdown(const int &p)
{
    node &now = A[p], &ls = A[p << 1], &rs = A[p << 1 | 1];
    if (now.tag == 0) return;
    if (now.tag == 1) //tag==1表示全修补
    {
        ls.lmax = ls.rmax = ls.mmax = 0;
        rs.lmax = rs.rmax = rs.mmax = 0;
        ls.sum = ls.len;
        rs.sum = rs.len;
    }
    else if (now.tag == -1) //tag==-1表示全挖空
    {
        ls.lmax = ls.rmax = ls.mmax = ls.len;
        rs.lmax = rs.rmax = rs.mmax = rs.len;
        ls.sum = 0;
        rs.sum = 0;
    }
    ls.tag = rs.tag = now.tag; //区间覆盖标记下传
    now.tag = 0;
}
void build(const int &l, const int &r, const int &p)
{
    A[p].l = l, A[p].r = r, A[p].sum = A[p].len = r - l + 1; //初始全1
    if (l == r) return;
    int mid = l + r >> 1;
    build(l, mid, p << 1), build(mid + 1, r, p << 1 | 1);
}
void clean(const int &p, const int &ll, const int &rr)
{
    node &now = A[p], &ls = A[p << 1], &rs = A[p << 1 | 1];
    if (now.l >= ll && now.r <= rr)
    {
        now.lmax = now.rmax = now.mmax = now.len;
        now.sum = 0;
        now.tag = -1;
        return;
    }
    pushdown(p);
    if (ll <= ls.r) clean(p << 1, ll, rr);
    if (rr >= rs.l) clean(p << 1 | 1, ll, rr);
    pushup(now, ls, rs);
}
int asksum(const int &p, const int &ll, const int &rr)
{
    node &now = A[p], &ls = A[p << 1], &rs = A[p << 1 | 1];
    if (now.l >= ll && now.r <= rr) return now.sum;
    pushdown(p);
    int res = 0;
    if (ll <= ls.r) res = asksum(p << 1, ll, rr);
    if (rr >= rs.l) res += asksum(p << 1 | 1, ll, rr);
    return res;
}
//返回值代表使用了多少
int canuse;
void repair(const int &p, const int &ll, const int &rr) //val代表还能填多少个1
{
    if (canuse <= 0) return; //剩余额度<=0则直接返回
    node &now = A[p], &ls = A[p << 1], &rs = A[p << 1 | 1];
    if (now.l >= ll && now.r <= rr)
    {
        if (canuse >= now.len - now.sum) //足够填满当前区间
        {
            canuse -= now.len - now.sum;
            now.lmax = now.rmax = now.mmax = 0;
            now.sum = now.len;
            now.tag = 1;
            return;
        }
        pushdown(p);
        repair(p << 1, ll, rr), repair(p << 1 | 1, ll, rr);
        pushup(now, ls, rs);
        return;
    }
    pushdown(p);
    if (ll <= ls.r) repair(p << 1, ll, rr);
    if (rr >= rs.l) repair(p << 1 | 1, ll, rr);
    pushup(now, ls, rs);
}
node askmax(const int &p, const int &ll, const int &rr) //询问最长连续0区间
{
    node &now = A[p], &ls = A[p << 1], &rs = A[p << 1 | 1];
    if (now.l >= ll && now.r <= rr) return now;
    pushdown(p);
    if (ll <= ls.r && rr >= rs.l) //询问区间两边都有，跨越中点
    {
        node lres = askmax(p << 1, ll, rr), rres = askmax(p << 1 | 1, ll, rr), res;
        pushup(res, lres, rres); //询问得到左半边、右半边答案，按左右区间方法上推
        return res;
    }
    else if (rr <= ls.r) return askmax(p << 1, ll, rr); //只在一边，直接向下递归
    else return askmax(p << 1 | 1, ll, rr);
}
int main()
{
    read(n), read(m);
    build(1, n, 1);
    while (m--)
    {
        int opt, l, r, l1, r1;
        read(opt), read(l), read(r);
        if (opt == 0) clean(1, l, r);
        else if (opt == 1)
        {
            read(l1), read(r1);
            canuse = asksum(1, l, r); //先询问得到可用的1的个数
            clean(1, l, r);           //清除区间
            repair(1, l1, r1);        //进行填补
        }
        else if (opt == 2) printf("%d\n", askmax(1, l, r).mmax);
    }
    return 0;
}
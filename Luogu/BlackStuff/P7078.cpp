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
const int maxn = 3e6 + 100;
int T, n, a[maxn], qh1, qt1, qh2, qt2, eaten;
struct snake
{
    int val, id;
    snake() { val = id = 0; }
    snake(int val, int id) { this->val = val, this->id = id; }
    bool operator<(const snake& b) const { return val != b.val ? val < b.val : id < b.id; }
    bool operator>(const snake& b) const { return val != b.val ? val > b.val : id > b.id; }
} q1[maxn], q2[maxn];
inline snake getmax()
{
    snake res;
    if (qt1 >= qh1) res = std::max(res, q1[qh1]);
    if (qt2 >= qh2) res = std::max(res, q2[qh2]);
    return res;
}
inline snake getmin()
{
    snake res;
    res.val = 1 << 30;
    if (qt1 >= qh1) res = std::min(res, q1[qt1]);
    if (qt2 >= qh2) res = std::min(res, q2[qt2]);
    return res;
}
inline void popmax()
{
    if(qt1 >= qh1 && qt2 >= qh2)
    {
        if (q1[qh1] > q2[qh2]) ++qh1; else ++qh2;
    }
    else if (qt1 >= qh1) ++qh1;
    else ++qh2;
}
int lastmin;
inline void popmin()
{
    if(qt1 >= qh1 && qt2 >= qh2) { if (q1[qt1] < q2[qt2]) --qt1, lastmin = 1; else --qt2, lastmin = 2; }
    else if (qt1 >= qh1) --qt1, lastmin = 1;
    else --qt2, lastmin = 2;
}
inline void recovermin()
{
    if(lastmin == 1) ++qt1; else if(lastmin == 2) ++qt2;
}
inline snake getsecmin()
{
    snake res;
    popmin(), res = getmin(), recovermin();
    return res;
}
inline int totalcount() { return std::max(0, qt1 - qh1 + 1) + std::max(0, qt2 - qh2 + 1); }
bool dfs()//搜索敢不敢吃
{
    if(totalcount() == 2) return 1;
    snake maxx = getmax(), minn = getmin(), secmin = getsecmin();
    maxx.val -= minn.val;
    if(maxx > secmin) return 1;
    else
    {
        popmax(), popmin(), q2[++qt2] = maxx;
        return !dfs();
    }
}
int main()
{
    read(T);
    for (int t = 1; t <= T; ++t)
    {
        if(t == 1) { read(n); for (int i = 1; i <= n; ++i) read(a[i]); }
        else { int k; read(k); for (int i = 1, p, x; i <= k; ++i) read(p), read(x), a[p] = x; }
        qh1 = qh2 = 1, qt1 = qt2 = 0, eaten = 0;
        for (int i = n; i; --i) q1[++qt1] = (snake){a[i], i};
        while(totalcount() >= 2)
        {
            snake maxx = getmax(), minn = getmin(), secmin = getsecmin();
            maxx.val -= minn.val;
            if (maxx > secmin) popmax(), popmin(), q2[++qt2] = maxx, ++eaten;
            else { eaten += dfs(); break; }
        }
        printf("%d\n", n - eaten);
    }
    return 0;
}
#include <algorithm>
#include <cstdio>
#include <ctype.h>
#include <vector>
using namespace std;
const int bufSize = 1e6;
inline char nc()
{
#ifdef DEBUG
    return getchar();
#endif
    static char buf[bufSize], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, bufSize, stdin), p1 == p2) ? EOF : *p1++;
}
inline void read(char* s)
{
    static char c;
    for (; !isalpha(c); c = nc())
        ;
    for (; isalpha(c); c = nc()) *s++ = c;
    *s = '\0';
}
template <typename T>
inline T read(T& r)
{
    static char c;
    static int flag;
    flag = 1, r = 0;
    for (c = nc(); !isdigit(c); c = nc())
        if (c == '-') flag = -1;
    for (; isdigit(c); c = nc()) r = r * 10 + c - 48;
    return r *= flag;
}
#define int long long
const int maxn = 5e5 + 100;
int n, llen, rlen, S[maxn], T[maxn], k;
vector<int> A[maxn], B[maxn];
int num1[maxn], num2[maxn];
int H1[maxn], H2[maxn], cnt1, cnt2;
int tree[maxn], timetag[maxn], nowtime;
int duplicate[maxn];
int flag1, flag2;
long long res;
inline int lowbit(const int& x) { return x & (-x); }
inline void clear() { ++nowtime; }
inline void check(int x)
{
    if (timetag[x] < nowtime) tree[x] = 0, timetag[x] = nowtime;
}
void add(int x, int k, int len)
{
    for (; x <= len; x += lowbit(x))
    {
        check(x);
        tree[x] += k;
    }
}
int ask(int x)
{
    int res = 0;
    for (; x > 0; x -= lowbit(x)) check(x), res += tree[x];
    return res;
}

signed main()
{
    read(n);
    while (n--)
    {
        read(llen);
        for (int i = 1; i <= llen; ++i) read(S[i]);
        read(rlen);
        for (int i = 1; i <= rlen; ++i) read(T[i]);
        read(k);
        if (llen != rlen) goto no;
        for (int i = 0; i < k; ++i) A[i].clear(), B[i].clear(), duplicate[i] = 0;
        for (int i = 1; i <= llen; ++i) A[i % k].push_back(S[i]), B[i % k].push_back(T[i]);
        for (int i = 0; i < k; ++i)
        {
            cnt1 = cnt2 = 0;
            for (auto it = A[i].begin(); it != A[i].end(); ++it)
                H1[++cnt1] = *it;
            sort(H1 + 1, H1 + cnt1 + 1);
            for (auto it = B[i].begin(); it != B[i].end(); ++it)
                H2[++cnt2] = *it;
            sort(H2 + 1, H2 + cnt2 + 1);
            for (int i = 1; i <= cnt1; ++i)
                if (H1[i] != H2[i]) goto no;
            cnt1 = unique(H1 + 1, H1 + cnt1 + 1) - H1 - 1;
            if (cnt1 != cnt2) duplicate[i] = 1;
            for (auto it = A[i].begin(); it != A[i].end(); ++it)
                *it = lower_bound(H1 + 1, H1 + 1 + cnt1, *it) - H1;
            for (auto it = B[i].begin(); it != B[i].end(); ++it)
                *it = lower_bound(H1 + 1, H1 + 1 + cnt1, *it) - H1;
            res = 0;
            for (auto it = A[i].begin(); it != A[i].end(); ++it)
            {
                res += ask(*it - 1);
                add(*it, 1, cnt1);
            }
            num1[i] = res & 1;
            clear();
            res = 0;
            for (auto it = B[i].begin(); it != B[i].end(); ++it)
            {
                res += ask(*it - 1);
                add(*it, 1, cnt1);
            }
            num2[i] = res & 1;
            clear();
        }
        flag1 = 1, flag2 = 1;
        for (int i = 0; flag1 && i < k; ++i)
            if (!duplicate[i] && num1[i] != num2[i]) flag1 = 0;
        for (int i = 0; flag2 && i < k; ++i)
            if (!duplicate[i] && num1[i] == num2[i]) flag2 = 0;
        if (flag1 || flag2) goto yes;
        goto no;
    yes:
        puts("TAK");
        continue;
    no:
        puts("NIE");
        continue;
    }
    return 0;
}
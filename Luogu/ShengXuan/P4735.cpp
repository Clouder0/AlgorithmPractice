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
inline void read(char *s)
{
    static char c;
    for (; !isalpha(c); c = nc());
    for (; isalpha(c); c = nc()) *s++ = c;
    *s = '\0';
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
const int maxn = 1e6 + 100;
int n, m, to[maxn * 20][2], root[maxn], cnt[maxn * 20], ind;
inline int newnode() { return ++ind; }
inline int copy(int x)
{
    int t = newnode();
    to[t][0] = to[x][0], to[t][1] = to[x][1], cnt[t] = cnt[x];
    return t;
}
int ins(int x, int k)
{
    x = copy(x);
    int newroot = x;
    for (int i = 30; i >= 0; --i)
    {
        int p = (k >> i) & 1;
        if(!to[x][p]) to[x][p] = newnode();
        else to[x][p] = copy(to[x][p]);
        x = to[x][p], ++cnt[x];
    }
    return newroot;
}
int ask(int l, int r, int k)
{
    int lp = root[l - 1], rp = root[r], res = 0;
    for (int i = 30; i >= 0; --i)
    {
        int p = (k >> i) & 1;
        if (cnt[to[rp][p ^ 1]] - cnt[to[lp][p ^ 1]] >= 1)
            res += 1 << i, lp = to[lp][p ^ 1], rp = to[rp][p ^ 1];
        else lp = to[lp][p], rp = to[rp][p];
    }
    return res;
}
int main()
{
    read(n), read(m);
    int pre = 0, len = n;
    root[0] = ins(root[0],0);
    for (int i = 1, x; i <= n; ++i) read(x), pre ^= x, root[i] = ins(root[i - 1], pre);
    for (int i = 1, l, r, x; i <= m; ++i)
    {
        static char s[10];
        read(s + 1);
        if (s[1] == 'A') read(x), pre ^= x, root[len + 1] = ins(root[len], pre), ++len;
        else read(l), read(r), read(x), printf("%d\n", ask(l - 1, r - 1, pre ^ x));
    }
    return 0;
}
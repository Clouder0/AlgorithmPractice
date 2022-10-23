#include <cstdio>
#include <algorithm>
#include <queue>
#include <ctype.h>
const int bufSize = 1e6;
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
int n, k;
struct node
{
    int len, cut;
    long long contri;
    bool operator<(const node& b) const { return contri < b.contri; }
};
priority_queue<node> q;
inline long long calc(int len, int cut)
{
    if (len == cut) return 0;
    int w = len / cut;
    int ones = len - w * cut;
    long long old = 1ll * (cut - ones) * w * w + 1ll * ones * (w + 1) * (w + 1);
    ++cut;
    w = len / cut;
    ones = len - w * cut;
    long long now = 1ll * (cut - ones) * w * w + 1ll * ones * (w + 1) * (w + 1);
    return old - now;
}
int main()
{
    read(k), read(n);
    long long res = 0;
    for (int i = 1, x; i <= k; ++i) read(x), q.push((node){x, 1, calc(x, 1)});
    k = n - k;
    while (k > 0)
    {
        if(q.empty()) break;
        node t = q.top();
        if(t.len == t.cut) break;
        q.pop();
        t.cut++, t.contri = calc(t.len, t.cut);
        q.push(t), --k;
    }
    while(!q.empty()) 
    {
        node t = q.top();
        int w = t.len / t.cut;
        int ones = t.len - w * t.cut;
        res += 1ll * (t.cut - ones) * w * w + 1ll * ones * (w + 1) * (w + 1);
        q.pop();
    }
    printf("%lld\n",res);
    return 0;
}
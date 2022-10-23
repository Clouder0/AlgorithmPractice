#include <cstdio>
#include <algorithm>
#include <ctype.h>
const int bufSize = 1e6;
#define int long long
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
const int maxn = 2e5 + 100;
int n;
struct node
{
    int a, b;
} A[maxn];
inline bool cmp(const node& a, const node& b) { return a.a < b.a; }
int sum[maxn], cnt[maxn],maxx,res;
inline void add(int x, int k) { for (; x <= maxx; x += x & -x) sum[x] += k,cnt[x]++; }
inline pair<int,int> ask(int x) { pair<int,int> res; for (; x > 0; x -= x & -x) res.first += sum[x],res.second += cnt[x]; return res; }
signed main()
{
    read(n);
    for (int i = 1; i <= n; ++i) read(A[i].a), read(A[i].b), maxx = max(maxx, A[i].b);
    sort(A + 1, A + 1 + n, cmp);
    
    for (int i = 1; i <= n; ++i) 
    {
        pair<int,int> t1 = ask(A[i].b),t2 = ask(maxx);
        res += A[i].a * ((A[i].b * t1.second - t1.first) + ((t2.first - t1.first) - A[i].b * (t2.second - t1.second)));
        add(A[i].b, A[i].b);
    }
    printf("%lld\n",res);
    return 0;
}
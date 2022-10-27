#include <algorithm>
#include <cstdio>
#include <ctype.h>
#include <map>
#include <set>
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
const int maxn = 2e5 + 100;
const int maxq = 800;
int n;
long long x, k;
int mex[maxq];
set<long long> all;
set<long long> S[maxq];
map<long long, long long> rem;
int main()
{
    scanf("%d", &n);
    while (n--)
    {
        char s[10];
        scanf("%s", s);
        if (s[0] == '+')
        {
            scanf("%lld", &x);
            if (all.find(x) != all.end()) continue;
            all.insert(x);
        }
        else if(s[0] == '-')
        {

        }
        else if (s[0] == '?')
        {
            scanf("%lld", &k);
            int res = 0;
            auto it = rem.find(k);
            if (it != rem.end()) res = it->second;
            while (all.find(1ll * k * (res + 1)) != all.end()) ++res;
            rem[k] = res;
            printf("%lld\n", 1ll * (res + 1) * k);
        }
    }
    return 0;
}
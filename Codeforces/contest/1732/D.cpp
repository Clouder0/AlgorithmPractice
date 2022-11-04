#include <algorithm>
#include <cstdio>
#include <ctype.h>
#include <map>
#include <vector>
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
int n;
long long x, k;
set<long long> all;
map<long long, set<long long>> del, in;
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
            all.insert(x);
        }
        else if(s[0] == '-')
        {
            scanf("%lld",&x);
            all.erase(x);
            for (auto it = in[x].begin(); it != in[x].end(); ++it) del[*it].insert(x);
        }
        else if (s[0] == '?')
        {
            scanf("%lld", &k);
            del[k].insert(k);
            long long res = k;
            in[k].insert(k);
            while(all.find(res) != all.end())
            {
                del[k].erase(res);
                if (del[k].empty()) del[k].insert(res + k);
                res = *del[k].begin(), in[res].insert(k);
            }
            printf("%lld\n",res);
        }
    }
    return 0;
}
#include <cstdio>
#include <algorithm>
#include <vector>
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
const int maxn = 401000;
const int maxx = 200000;
int n;
char s[10];
vector<int> hrY[maxn], hlY[maxn];
vector<int> vuX[maxn], vdX[maxn];
vector<int> ua[maxn], da[maxn],la[maxn],ra[maxn],um[maxn],dm[maxn],lm[maxn],rm[maxn];
int X[maxn], Y[maxn];
int ADD[maxn], MINUS[maxn];
signed main()
{
    read(n);
    for (int i = 1; i <= n; ++i) 
    {
        int x,y;
        read(x), read(y), read(s + 1);
        if (s[1] == 'U') vuX[x].push_back(y), um[x - y + maxx].push_back(x), ua[x + y].push_back(x);
        else if (s[1] == 'D') vdX[x].push_back(y), da[x + y].push_back(x), dm[x - y + maxx].push_back(x);
        else if (s[1] == 'L') hlY[y].push_back(x), la[x + y].push_back(x), lm[x - y + maxx].push_back(x);
        else if (s[1] == 'R') hrY[y].push_back(x), rm[x - y + maxx].push_back(x), ra[x + y].push_back(x);
        X[i] = x, Y[i] = y;
        MINUS[i] = x - y + maxx, ADD[i] = x + y;
    }
    int xnum, ynum, addnum, minusnum;
    std::sort(X + 1, X + 1 + n); 
    std::sort(Y + 1, Y + 1 + n); 
    std::sort(ADD + 1, ADD + 1 + n); 
    std::sort(MINUS + 1, MINUS + 1 + n);
    xnum = std::unique(X + 1, X + 1 + n) - X - 1; 
    ynum = std::unique(Y + 1, Y + 1 + n) - Y - 1; 
    addnum = std::unique(ADD + 1, ADD + 1 + n) - ADD - 1; 
    minusnum = std::unique(MINUS + 1, MINUS + 1 + n) - MINUS - 1;
    int tans = 1 << 30;
    for (int i = 1; i <= xnum; ++i)
    {
        int x = X[i];
        std::sort(vuX[x].begin(), vuX[x].end());
        std::sort(vdX[x].begin(), vdX[x].end());
        for (vector<int>::iterator it = vuX[x].begin(), p = vdX[x].begin(); it != vuX[x].end(); ++it)
        {
            while(p != vdX[x].end() && *it > *p) ++p;
            if(p == vdX[x].end()) break;
            tans = std::min(tans,(*p - *it) * 5);
        }
    }
    for (int i = 1; i <= ynum; ++i)
    {
        int y = Y[i];
        std::sort(hlY[y].begin(), hlY[y].end());
        std::sort(hrY[y].begin(), hrY[y].end());
        for (vector<int>::iterator it = hrY[y].begin(), p = hlY[y].begin(); it != hrY[y].end(); ++it)
        {
            while(p != hlY[y].end() && *it > *p) ++p;
            if(p == hlY[y].end()) break;
            tans = std::min(tans,(*p - *it) * 5);
        }
    }
    for (int i = 1; i <= addnum; ++i)
    {
        int pos = ADD[i];
        std::sort(ua[pos].begin(), ua[pos].end());
        std::sort(ra[pos].begin(), ra[pos].end());
        for (vector<int>::iterator it = ra[pos].begin(),p = ua[pos].begin(); it != ra[pos].end(); ++it)
        {
            while(p != ua[pos].end() && *it > *p) ++p;
            if(p == ua[pos].end()) break;
            tans = std::min(tans,(*p - *it) * 10);
        }
        std::sort(da[pos].begin(),da[pos].end());
        std::sort(la[pos].begin(),la[pos].end());
        for (vector<int>::iterator it = da[pos].begin(),p = la[pos].begin(); it != da[pos].end(); ++it)
        {
            while(p != la[pos].end() && *it > *p) ++p;
            if(p == la[pos].end()) break;
            tans = std::min(tans,(*p - *it) * 10);
        }
    }
    for (int i = 1; i <= minusnum; ++i)
    {
        int pos = MINUS[i];
        std::sort(um[pos].begin(), um[pos].end());
        std::sort(lm[pos].begin(), lm[pos].end());
        for (vector<int>::iterator it = um[pos].begin(), p = lm[pos].begin(); it != um[pos].end(); ++it)
        {
            while(p != lm[pos].end() && *it > *p) ++p;
            if(p == lm[pos].end()) break;
            tans = std::min(tans,(*p - *it) * 10);
        }
        std::sort(dm[pos].begin(), dm[pos].end());
        std::sort(rm[pos].begin(), rm[pos].end());
        for (vector<int>::iterator it = rm[pos].begin(), p = dm[pos].begin(); it != rm[pos].end(); ++it)
        {
            while(p != dm[pos].end() && *it > *p) ++p;
            if(p == dm[pos].end()) break;
            tans = std::min(tans,(*p - *it) * 10);
        }
    }
    if(tans == 1<<30) puts("SAFE");
    else printf("%lld\n",tans);
    return 0;
}
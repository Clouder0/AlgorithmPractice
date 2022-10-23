#include <cstdio>
#include <queue>
#include <algorithm>
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
int R,G,B;
priority_queue<int> rq,gq,bq;
int main()
{
    read(R),read(G),read(B);
    for(int i = 1;i<=R;++i)
    {
        int x;
        read(x),rq.push(x);
    }
    for(int i = 1;i<=G;++i)
    {
        int x;
        read(x),gq.push(x);
    }
    for(int i = 1;i<=B;++i)
    {
        int x;
        read(x),bq.push(x);
    }
    long long ans = 0;
    while(!rq.empty() && !gq.empty() && !bq.empty())
    {
        int r = rq.top(),g = gq.top(),b = bq.top();
        int minn = std::min(r,std::min(g,b));
        if(minn == r)
        {
            ans += g * b;
            gq.pop(),bq.pop();
        }
        else if(minn == g)
        {
            ans += r * b;
            rq.pop(),bq.pop();
        }
        else if(minn == b)
        {
            ans += r * g;
            rq.pop(),gq.pop();
        }
    }
    while(!rq.empty() && !gq.empty()) ans += rq.top() * gq.top(),rq.pop(),gq.pop();
    while(!rq.empty() && !bq.empty()) ans += rq.top() * bq.top(),rq.pop(),bq.pop();
    while(!gq.empty() && !bq.empty()) ans += gq.top() * bq.top(),gq.pop(),bq.pop();
    printf("%lld\n",ans);
    return 0;
}
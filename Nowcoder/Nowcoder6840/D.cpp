
#include <cstdio>
#include <queue>
#include <cstring>
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
const int maxn = 100100;
int m,n;
bool vis[maxn];
int main()
{
    read(m),read(n);
    queue<pair<int,int> > q;
    q.push(make_pair(n,0));
    while(!q.empty())
    {
        int u = q.front().first,t = q.front().second;
        q.pop();
        if(u == m)
        {
            printf("%d\n",t);
            return 0;
        }
        if(!vis[u+1] && u + 1 <= 100000) q.push(make_pair(u + 1,t + 1)),vis[u+1]=1;
        if(!vis[u-1] && u - 1 > 0) q.push(make_pair(u - 1,t + 1)),vis[u-1]=1;
        if(!vis[u*2] && u * 2 <= 100000) q.push(make_pair(u*2,t + 1)),vis[u*2]=1;
    }
    return 0;
}

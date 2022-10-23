#include <cstdio>
#include <set>
#include <vector>
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
const int maxn = 1e5 + 100;
int x,n,m;
int fa[maxn];
int find(int x){return x == fa[x] ? x : fa[x] = find(fa[x]);}
void unite(int x,int y)
{
    x = find(x),y = find(y);
    if(x == y) return;
    fa[x] = y;
}
set<int> output;
vector<int> has[maxn],bel[maxn];
int main()
{
    read(x),read(n),read(m);
    for (int i = 1; i <= m; ++i) fa[i] = i;
    for (int i = 1; i <= m; ++i)
    {
        int x,z;
        read(z);
        while(z--) 
        {
            read(x);
            has[i].push_back(x);
            bel[x].push_back(i);
        }
    }
    for (int i = 0; i < x; ++i)
        for (vector<int>::iterator it = bel[i].begin(); it != bel[i].end(); ++it) unite(*it, bel[i][0]);
    if(bel[n].size() == 0)
    {
        printf("1 %d",n);
        return 0;
    }
    int xx = find(bel[n][0]);
    for (int i = 1; i <= m; ++i)
    {
        if(find(i) == xx) 
        {
            for(vector<int>::iterator it = has[i].begin();it!=has[i].end();++it) output.insert(*it);
        }
    }
    printf("%d ",output.size());
    for(set<int>::iterator it = output.begin();it!=output.end();++it) printf("%d ",*it);
    return 0;
}
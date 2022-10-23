#include <cstdio>
#include <queue>
#include <algorithm>
#include <ctype.h>
const int bufSize = 1e6;
#define DEBUG
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
const int maxn = 300;
int n,m;
int r[maxn],c[maxn];
int a[maxn][maxn];
queue<pair<int,int> > q;
int main()
{
    read(n),read(m);
    for(int i = 1;i<=n;++i) for(int j = 1;j<=m;++j)
    {
        int x;
        read(x),r[i] = std::max(r[i],x),c[j] = std::max(c[j],x);
    }
    sort(r + 1,r + 1 + n),sort(c + 1,c + 1 + m);
    int x = 0,y = 0,i = n,j = m; 
    for(int num = n * m;num;--num)
    {
        if(r[i] == num) ++x;
        if(c[j] == num) ++y;
        if(r[i] == num || c[j] == num) a[x][y] = num;
        else a[q.front().first][q.front().second] = num,q.pop();
        if(r[i] == num)
        {
            //num is max in row i,so positions before it is ok
            for(int k = y - 1;k > 0;--k) q.push(make_pair(x,k));
            --i;
        }
        if(c[j] == num)
        {
            for(int k = x - 1;k > 0;--k) q.push(make_pair(k,y));
            --j;
        }
    }
    for(int i = 1;i<=n;putchar('\n'),++i) for(int j = 1;j<=m;++j) printf("%d ",a[i][j]);
    return 0;
}
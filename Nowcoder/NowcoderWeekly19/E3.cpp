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
    for (; c != '.' && c != '#'; c = nc());
    for (; c == '.' || c == '#'; c = nc()) *s++ = c;
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
const int maxn = 2e6 + 100;
vector<char> a[maxn];
char s[maxn];
int n,m,ans,siz,flag;
int dx[4] = {1,-1,0,0};
int dy[4] = {0,0,1,-1};
void dfs(int x,int y)
{
    ++siz;
    a[x][y] = 'a';
    for(int i = 0;i<4;++i)
    {
        int nx = x + dx[i],ny = y + dy[i];
        if(nx < 0 || nx >= n || ny < 0 || ny >= m) {flag = 1;continue;}
        if(a[nx][ny] == '.') dfs(nx,ny);
    }
}
int main()
{
    read(n),read(m);
    for(int i = 0;i < n;++i)
    {
        read(s);
        for(int j = 0;j < m;++j) a[i].push_back(s[j]);
    }
    for(int i = 0;i < n;++i)
    {
        for(int j = 0;j<m;++j)
        {
            if(a[i][j] == '#') ++ans;
            else if(a[i][j] == '.')
            {
                flag = 0,siz = 0;
                dfs(i,j);
                if(!flag) ans += siz;
            }
        }
    }
    printf("%d\n",ans);
    return 0;
}
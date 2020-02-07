#include <cstdio>
#include <memory.h>
using namespace std;
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
int n;
char s[210];
int fa[210];
int size[210];
int find(const int &x)
{
    return fa[x] == x ? x : fa[x] = find(fa[x]);
}
void unite(const int &x,const int &y)
{
    int a = find(x),b = find(y);
    if(a == b)
        return;
    fa[a] = b;
    size[b] += size[a];
    size[a] = 0;
}
int tot;
int col[210];
int main()
{
    read(n);
    for(int i = 1;i<=n*2;++i)
        fa[i] = i,size[i] = 1;
    scanf("%s",s+1);
    for(int i = 1;i<=n;++i)
    {
        for(int j = i+1;j<=n;++j)
        {
            if(s[i] > s[j])
            {
                if(find(i) == find(j) || find(i+n) == find(j+n))
                {
                    puts("NO");
                    return 0;
                }
                unite(i,j+n);
                unite(i+n,j);
            }
        }
    }
    memset(col,-1,sizeof(col));
    for(int i = 1;i<=n;++i)
    {
        col[i] = 0;
        for(int j = 1;j<=n;++j)
        {
            if(find(i+n) == find(j))
            {
                if(col[j] == -1)
                    col[j] = col[i] ^ 1;
                else if(col[i] == col[j])
                {
                    puts("NO");
                    return 0;
                }
            }
            else
            {
                if(col[j] == -1)
                    col[j] = col[i];
                else if(col[j] != col[i])
                {
                    puts("NO");
                    return 0;
                }
            }
        }
    }
    for(int i = 1;i<=n;++i)
        putchar(col[i]+48);
    return 0;
}
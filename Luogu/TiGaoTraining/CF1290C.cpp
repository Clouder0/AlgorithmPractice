#include <cstdio>
template<typename T>
inline T min(const T &a,const T &b){return a<b?a:b;}
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
const int maxn = 3e5 + 100;
int n,k,ans;
char s[maxn];
int fa[maxn*3],val[maxn*3];
inline int find(const int &x){return fa[x] == x ? x : fa[x] = find(fa[x]);}
inline void merge(int x,int y)
{
    x = find(x),y = find(y);
    if(x == y) return;
    fa[x] = y;
    val[y] += val[x];
}
int belong[maxn][2];
inline int get(int x)
{
    return min(val[find(x)],val[find(x+k)]);
}
int main()
{
    read(n),read(k);
    scanf("%s",s+1);
    for(int i = 1;i<=k;++i)
    {
        int num,x;
        read(num);
        for(int j = 1;j<=num;++j)
        {
            read(x);
            belong[x][belong[x][0] > 0] = i;
        }
    }
    for(int i = 1;i<=k*2 + 1;++i)
        fa[i] = i,val[i] = i > k;
    val[k*2+1] = 1<<30;
    for(int i = 1;i<=n;++i)
    {
        if(belong[i][1])
        {
            if(s[i] == '0' && find(belong[i][0]) != find(belong[i][1] + k))
            {
                ans -= get(belong[i][0]) + get(belong[i][1]);
                merge(belong[i][0],belong[i][1] + k),merge(belong[i][1],belong[i][0] + k);
                ans += get(belong[i][0]);
            }
            else if(s[i] == '1' && find(belong[i][0]) != find(belong[i][1]))
            {
                ans -= get(belong[i][0]) + get(belong[i][1]);
                merge(belong[i][0],belong[i][1]),merge(belong[i][0] + k,belong[i][1] + k);
                ans += get(belong[i][0]);
            }
        }
        else if(belong[i][0])
        {
            ans -= get(belong[i][0]);
            merge(belong[i][0] + k * (s[i] - 48),k*2+1);
            ans += get(belong[i][0]);
        }
        printf("%d\n",ans);
    }
    return 0;
}
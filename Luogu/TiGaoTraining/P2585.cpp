#include <cstdio>
#include <cstring>
using namespace std;
template<typename T>
inline T max(const T &a,const T &b){return a>b?a:b;}
template<typename T>
inline T min(const T &a,const T &b){return a<b?a:b;}
const int maxn = 5e5 + 10;
char s[maxn];
int n;
int f[maxn][3];//0 green 1 blue 2 red
int t[maxn][3];
int p = 1;
void dfs(int u)
{
    int flag = s[p++] - 48;
    if(flag == 0)
    {
        f[u][0] = 1;
        f[u][1] = f[u][2] = 0;
        t[u][0] = 1;
        t[u][1] = t[u][2] = 0;
        return;
    }
    else if(flag == 1)
    {
        int v = u + 1;
        dfs(v);
        f[u][0] = max(f[v][1],f[v][2]) + 1;
        f[u][1] = max(f[v][0],f[v][2]);
        f[u][2] = max(f[v][0],f[v][1]);
        t[u][0] = min(t[v][1],t[v][2]) + 1;
        t[u][1] = min(t[v][0],t[v][2]);
        t[u][2] = min(t[v][0],t[v][1]);
        return;
    }
    else
    {
        int ls = u + 1,rs = u + 2;
        dfs(ls);
        dfs(rs);
        f[u][0] = max(f[ls][1] + f[rs][2],f[ls][2] + f[rs][1]) + 1;
        f[u][1] = max(f[ls][0] + f[rs][2],f[ls][2] + f[rs][0]);
        f[u][2] = max(f[ls][0] + f[rs][1],f[ls][1] + f[rs][0]);
        t[u][0] = min(t[ls][1] + t[rs][2],t[ls][2] + t[rs][1]) + 1;
        t[u][1] = min(t[ls][0] + t[rs][2],t[ls][2] + t[rs][0]);
        t[u][2] = min(t[ls][0] + t[rs][1],t[ls][1] + t[rs][0]);
    }
}
int main()
{
    scanf("%s",s+1);
    n = strlen(s+1);
    dfs(1);
    printf("%d %d",max(max(f[1][0],f[1][1]),f[1][2]),min(min(t[1][0],t[1][1]),t[1][2]));
    return 0;
}
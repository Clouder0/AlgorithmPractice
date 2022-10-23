#include <cstdio>
#include <cstring>
using namespace std;
int n,m;
int sa[31][31];
int dfs(int now,int step)
{
    if(step == m)
        return now == 1;
    if(sa[now][step] != -1)
        return sa[now][step];
    int ans = 0;
    if(now == 1)
        ans += dfs(n,step+1);
    else
        ans += dfs(now-1,step+1);
    if(now == n)
        ans += dfs(1,step+1);
    else
        ans += dfs(now+1,step+1);
    sa[now][step] = ans;
    return ans;
}
void read(int &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
int main()
{
    memset(sa,-1,sizeof(sa));
    read(n);
    read(m);
    printf("%d",dfs(1,0));
    return 0;
}
#include <cstdio>
using namespace std;
template<typename T>
inline void _swap(T &a,T &b)
{
    T t = a;
    a = b;
    b = t;
}
int T;
char temp[10];
int s[6][6];
int tar[6][6] = 
{
    {0,0,0,0,0,0},
    {0,1,1,1,1,1},
    {0,0,1,1,1,1},
    {0,0,0,2,1,1},
    {0,0,0,0,0,1},
    {0,0,0,0,0,0}
};
int dx[9] = {0,-1,-2,-1,-2,1,2,1,2};
int dy[9] = {0,-2,-1,2,1,-2,-1,2,1};
int maxdeep;
bool flag;
inline int eva()
{
    int res = 0;
    for(int i = 1;i<=5;++i)
        for(int j = 1;j<=5;++j)
            if(s[i][j] != tar[i][j])
                ++res;
    return res;
}
void dfs(int x,int y,int step)
{
    int e = eva();
    if(flag)
        return;
    if(step == maxdeep)
    {
        flag = flag||!e;
        return;
    }
    int nx,ny;
    for(int i = 1;i<=8;++i)
    {
        nx = x + dx[i];
        ny = y + dy[i];
        if(nx < 1 || nx > 5 || ny < 1 || ny > 5)
            continue;
        _swap(s[nx][ny],s[x][y]);
        if(eva() + step <= maxdeep)
            dfs(nx,ny,step+1);
        _swap(s[nx][ny],s[x][y]);
    }
}
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        flag = false;
        int sx,sy;
        for(int i = 1;i<=5;++i)
        {
            scanf("%s",temp+1);
            for(int j = 1;j<=5;++j)
                if(temp[j] == '*')
                    s[i][j] = 2,sx = i,sy = j;
                else
                    s[i][j] = temp[j] - '0';
        }
        for(maxdeep = 0;maxdeep<=15;++maxdeep)
        {
            dfs(sx,sy,0);
            if(flag)
            {
                printf("%d\n",maxdeep);
                break;
            }
        }
        if(!flag)
            puts("-1");
    }
    return 0;
}
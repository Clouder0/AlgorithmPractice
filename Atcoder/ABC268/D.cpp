#include <cstdio>
#include <cstring>
#include <map>
#include <string>
using namespace std;
const int maxm = 1e5 + 100;
int n, m;
int ls[100];
char s[100][200], t[100];
map<string, bool> mp;
char now[200];
bool used[100];
bool flag;
void dfs(int len, int num)
{
    if(flag) return;
    if(len > 16) return;
    if(num == n && len >= 3)
    {
        string ns = now + 1;
        if(mp[ns]) goto fail;
        flag = 1;
        for (int i = 1; i <= len; ++i) putchar(now[i]);
        return;
    }
//    printf("%s\n",now + 1);
    fail:
        for (int i = 1; i <= n; ++i)
        {
            if (used[i]) continue;
            used[i] = 1;
            for (int j = 1; len + j + ls[i] <= 16; ++j)
            {
                for (int k = 1; k <= j; ++k) now[len + k] = '_';
                for (int k = 1; k <= ls[i]; ++k) now[len + j + k] = s[i][k];
                now[len + j + ls[i] + 1] = '\0';
                dfs(len + j + ls[i], num + 1);
                if(flag) return;
            }
            used[i] = 0;
            if(flag) return;
        }
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) scanf("%s", &s[i][1]), ls[i] = strlen(&s[i][1]);
    for (int i = 1; i <= m; ++i) 
    {
        scanf("%s", &t[1]);
        string tmp = t + 1;
        mp[tmp] = 1;
    }
    for (int i = 1; !flag && i <= n; ++i)
    {
        for (int j = 1; j <= ls[i]; ++j) now[j] = s[i][j];
        now[ls[i] + 1] = '\0';
        used[i] = 1;
        dfs(ls[i], 1);
        used[i] = 0;
        if(flag) return 0;
    }
    if (!flag)
        puts("-1");
    return 0;
}
#include <cstdio>
using namespace std;
bool hasfa[256],exist[256];
int ls[256], rs[256];
int n;
void dfs(const int &now)
{
    if (now == '*')
        return;
    putchar(now);
    dfs(ls[now]);
    dfs(rs[now]);
}
char a[5];
int main()
{
    scanf("%d", &n);
    while (n--)
    {
        scanf("%s", a + 1);
        exist[a[1]] = exist[a[2]] = hasfa[a[2]] = exist[a[3]] = hasfa[a[3]] = true;
        ls[a[1]] = a[2];
        rs[a[1]] = a[3];
    }
    for (int i = 1;i <= 255; ++i)
        if (exist[i] && !hasfa[i])
        {
            dfs(i);
            return 0;
        }
}
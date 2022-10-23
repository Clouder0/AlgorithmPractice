
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
template <typename T>
void read(T &r)
{
    static char c;
    r = 0;
    for (c = getchar(); c > '9' || c < '0'; c = getchar())
        ;
    for (; c >= '0' && c <= '9'; r = (r << 1) + (r << 3) + (c ^ 48), c = getchar())
        ;
}
int T, tot[2][27], last[27], pre[1000100][27];
char s[1000100], t[1000100];
int sl,tl;
int main()
{
    read(T);
    while (T--)
    {
        bool flag = true;
        int ans = 0;
        scanf("%s%s", &s, &t);
        sl = strlen(s);
        tl = strlen(t);
        memset(tot, 0, sizeof(tot));
        memset(pre, -1, sizeof(pre));
        for (int i = 0; i < sl; i++)
            tot[0][s[i] - 'a']++;
        for (int i = sl - 1; i >= 0; pre[i][s[i] - 'a'] = i--)
            for (int j = 0; j < 26; j++)
                pre[i][j] = pre[i + 1][j];
        for (int i = 0; i < tl; i++)
            tot[1][t[i] - 'a']++;
        for (int i = 0; flag && i < 26; i++)
            if (tot[1][i] && !tot[0][i])
                flag = false;
        if (!flag)
        {
            printf("-1\n");
            continue;
        }
        int i = 0, j = 0;
        while (i < tl)
        {
            while (pre[j][t[i] - 'a'] != -1)
            {
                j = pre[j][t[i] - 'a'] + 1;
                i++;
            }
            ans++;
            j = 0;
        }
        printf("%d\n", ans);
    }
    return 0;
}

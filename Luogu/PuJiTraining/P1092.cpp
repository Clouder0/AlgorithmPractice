#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;
int n;
char s[4][30];
bool used[30];
int ltn[30];
void dfs(int pos, int status, int frontadd)
{
    if (pos == 0)
    {
        if (frontadd)
            return; //最高位进位，不可行
        for (int i = 1; i <= n; ++i)
            printf("%d ", ltn[i]);
        exit(0);
    }
    int w1, w2, w3;//题解的玄学剪枝……
    for (int i = pos - 1; i; --i)
    {
        w1 = ltn[s[1][i]];
        w2 = ltn[s[2][i]];
        w3 = ltn[s[3][i]];
        if (w1 == -1 || w2 == -1 || w3 == -1)
            continue;
        if ((w1 + w2) % n != w3 && (w1 + w2 + 1) % n != w3)
            return;
    }
    if (status == 3)
    {
        int sum = ltn[s[1][pos]] + ltn[s[2][pos]] + frontadd;
        frontadd = 0;
        if (sum >= n)
            sum -= n, frontadd = 1;
        if (used[sum] && ltn[s[3][pos]] != sum)
            return;
        if (ltn[s[3][pos]] != -1 && ltn[s[3][pos]] != sum)
            return;
        if (ltn[s[3][pos]] == sum)
        {
            dfs(pos - 1, 1, frontadd);
            return;
        }
        ltn[s[3][pos]] = sum;
        used[sum] = true;
        dfs(pos - 1, 1, frontadd);
        ltn[s[3][pos]] = -1;
        used[sum] = false;
        return;
    }
    if (ltn[s[status][pos]] == -1)
    {
        //没有赋值，那就给值
        for (int i = n - 1; i >= 0; --i)
        {
            if (used[i])
                continue;
            ltn[s[status][pos]] = i;
            used[i] = true;
            dfs(pos, status + 1, frontadd);
            ltn[s[status][pos]] = -1;
            used[i] = false;
        }
        return;
    }
    dfs(pos, status + 1, frontadd);
}
int main()
{
    scanf("%d", &n);
    scanf("%s", s[1] + 1);
    scanf("%s", s[2] + 1);
    scanf("%s", s[3] + 1);
    for (int i = 1; i <= n; ++i)
        s[1][i] -= 'A' - 1, s[2][i] -= 'A' - 1, s[3][i] -= 'A' - 1;
    memset(ltn, -1, sizeof(ltn));
    dfs(n, 1, 0);
    return 0;
}
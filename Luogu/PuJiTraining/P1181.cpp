#include <cstdio>
using namespace std;
int n, m;
int all[100001];
int main()
{
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; ++i)
        scanf("%d", all + i);
    int temp = 0, ans = 1;
    for (int i = 1; i <= n; ++i)
        if (temp + all[i] <= m)
            temp += all[i];
        else
            ++ans, temp = all[i];
    printf("%d", ans);
    return 0;
}
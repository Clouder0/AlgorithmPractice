#include <iostream>
#include <string>
using namespace std;
string words[22];
char start;
int n, ans, nowl;
int used[21];
inline int min(const int &a, const int &b)
{
    return a < b ? a : b;
}
inline int max(const int &a, const int &b)
{
    return a > b ? a : b;
}
int calc(const string &str1, const string &str2)
{
    static int l, i, j;
    l = min(str1.length(), str2.length());
    for (i = 1; i < l; ++i) //枚举重叠部分长度，因为包含无贡献，因此包含情况视作无重叠
    {
        for (j = 0; j < i; ++j)
            if (str1[str1.length() - i + j] != str2[j])
                goto restart;
        return i;
    restart:;
    }
    return 0;
}
void dfs(int now)
{
    ans = max(ans, nowl);
    int t;
    for (int i = 1; i <= n; ++i)
    {
        if (used[i] >= 2)
            continue;
        t = calc(words[now], words[i]);
        if (t == 0)
            continue;
        nowl += words[i].length() - t; //增加延伸长度，即去掉重叠部分的长度
        ++used[i];
        dfs(i);
        --used[i];
        nowl -= words[i].length() - t;
    }
}
int main()
{
    cin >> n;
    for (int i = 1; i <= n; ++i)
        cin >> words[i];
    cin >> start; //录入开始的字符
    for (int i = 1; i <= n; ++i)
    {
        if (words[i][0] == start)
        {
            nowl = words[i].length();
            ++used[i];
            dfs(i);
            --used[i];
        }
    }
    printf("%d", ans);
    return 0;
}
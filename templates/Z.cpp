/*
Z函数：计算 $z(i)$ 时：

- 若 $i \le r$ ：
  根据定义有 $s[i,r] = s[i-l,r-l]$ ，那么 $z(i) \ge \min(z(i-l),r - i + 1)$ .
  此时：

  - 若 $z(i - l) < r - i + 1$ ，则 $z(i) = z(i - l)$ .
  - 若 $z(i - l) \ge r - i + 1$ ，则令 $z(i) = r - i + 1$ ，然后用((20210112201318-cf7ikov "朴素算法"))扩展。
- 若 $i > r$ ：
  直接按照朴素算法，暴力求出 $z(i)$ .
- 求出 $z(i)$ 后，更新 $l,r$ 的值。

*/
#include <cstdio>
#include <cstring>
const int maxn = 1e6 + 100;
char s[maxn];
int n, z[maxn];
int main()
{
    scanf("%s", s);
	n = strlen(s);
    int l = 0, r = 0;
    for (int i = 1; i < n; ++i)
    {
        if (i <= r)
        {
            if (z[i - l] < r - i + 1) z[i] = z[i - l];//注意此处不能取等，长度相同需要向后继续匹配
            else for (z[i] = r - i + 1; i + z[i] < n && s[i + z[i]] == s[z[i]]; ++z[i]) ;
        }
        else for (; i + z[i] < n && s[i + z[i]] == s[z[i]]; ++z[i]);
        if (i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
    }
    for (int i = 0; i < n; ++i) printf("%d\n", z[i]);
    return 0;
}
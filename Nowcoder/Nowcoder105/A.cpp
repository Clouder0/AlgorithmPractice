#include <cstdio>
const int maxn = 210;
int T;
char s[maxn];
int num[maxn], type[maxn], cnt;
void output(int i)
{
    for (int t = 0; t < num[i]; ++t) putchar('0' + type[i]);
}
bool cmp(int l1, int r1, int l2, int r2)
{
    while (l1 <= r1 && l2 <= r2)
    {
        if (num[l1] != num[l2])
        {
            if (type[l1]) return num[l1] > num[l2];
            return num[l1] < num[l2];
        }
        ++l1, ++l2;
    }
    return r1 - l1 <= r2 - l2;
}
int main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%s", s + 1);
        cnt = 0;
        int p = 2;
        num[++cnt] = 1, type[1] = s[1] - '0';
        while (s[p] != '\0')
        {
            if (s[p] == s[p - 1])
                ++num[cnt];
            else
            {
                num[++cnt] = 1;
                type[cnt] = s[p] - '0';
            }
            ++p;
        }
        int l = 1, r = 2;
        if (type[1]) output(1), putchar(' '), l = 2, r = 3;
        while (l <= cnt && r <= cnt)
        {
            if (r + 2 <= cnt && type[r + 1] == 0 && type[r + 2] == 1)
            {
                if (num[r + 1] < num[l])
                {
                    r += 2;
                    continue;
                }
                else if (num[r + 1] == num[l])
                {
                    if (num[l + 1] < num[r + 2])
                    {
                        r += 2;
                        continue;
                    }
                    else if (num[l + 1] == num[r + 2])
                    {
                        if (cmp(l + 2, r + 2, l, r))
                        {
                            r += 2;
                            continue;
                        }
                        else
                            goto no;
                    }
                    else
                        goto no;
                }
                else
                    goto no;
            }
            break;
        no:
            for (int i = l; i <= r; ++i) output(i);
            putchar(' ');
            l = r + 1, r = l + 1;
        }
        if(r > cnt) r = cnt;
        for (int i = l; i <= r; ++i) output(i);
        putchar(' ');
        if(r < cnt) output(cnt);
        puts("");
    }
    return 0;
}
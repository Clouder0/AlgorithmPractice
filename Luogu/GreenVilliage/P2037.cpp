#include <cstdio>

const int maxn = 1e5 + 100;
const int maxm = 1e7 + 100;
int n, num[maxm];
char s[maxn];
int ton[300];
int main()
{
    ton['A'] = ton['B'] = ton['C'] = 2;
    ton['D'] = ton['E'] = ton['F'] = 3;
    ton['G'] = ton['H'] = ton['I'] = 4;
    ton['J'] = ton['K'] = ton['L'] = 5;
    ton['M'] = ton['N'] = ton['O'] = 6;
    ton['P'] = ton['R'] = ton['S'] = 7;
    ton['T'] = ton['U'] = ton['V'] = 8;
    ton['W'] = ton['X'] = ton['Y'] = 9;
    for (int i = 0; i <= 9; ++i) ton['0' + i] = i;
    scanf("%d", &n);
    while (n--)
    {
        scanf("%s", s + 1);
        int now = 0;
        for (char* p = s + 1; *p != '\0'; ++p)
        {
            if (*p == '-') continue;
            now = now * 10 + ton[*p];
        }
        num[now]++;
    }
    int flag = 0;
    for (int i = 0; i < 10000000; ++i)
        if (num[i] > 1)
        {
            int pre = i / 10000;
            int suf = i % 10000;
            printf("%.3d-%.4d %d\n", pre, suf, num[i]);
            flag = 1;
        }
    if (!flag) puts("No duplicates.");
    return 0;
}
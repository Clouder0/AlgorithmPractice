#include <cstdio>
#include <algorithm>
#include <cstring>
#include <ctype.h>
const int bufSize = 1e6;
inline char nc()
{
    #ifdef DEBUG
    return getchar();
    #endif
    static char buf[bufSize], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, bufSize, stdin), p1 == p2) ? EOF : *p1++;
}
template<typename T>
inline T read(T &r)
{
    static char c;
    static int flag;
    flag = 1, r = 0;
    for (c = nc(); !isdigit(c); c = nc()) if (c == '-') flag = -1;
    for (; isdigit(c); c = nc()) r = r * 10 + c - 48;
    return r *= flag;
}
const int maxn = 50;
const int digit = 10000;
struct HP
{
    int a[maxn];
    HP() { memset(a, 0, sizeof(a)), a[0] = 1; }
    HP operator+(const HP b) const
    {
        HP c;
        c.a[0] = std::max(a[0], b.a[0]);
        for (int i = 1; i <= c.a[0]; ++i)
        {
            c.a[i] += a[i] + b.a[i];
            if (c.a[i] >= digit) c.a[i + 1]++, c.a[i] -= digit;
        }
        if (c.a[c.a[0] + 1] > 0) ++c.a[0];
        return c;
    }
    HP operator-(const HP b) const
    {
        HP c;
        c.a[0] = a[0];
        for (int i = 1; i <= a[0]; ++i) 
        {
            c.a[i] += a[i] - b.a[i];
            if(c.a[i] < 0) c.a[i] += digit,--c.a[i+1];
        }
        while (c.a[0] > 1 && c.a[c.a[0]] == 0) --c.a[0];
        return c;
    }
    HP operator*(const HP b) const
    {
        HP c;
        c.a[0] = a[0] + b.a[0];
        for (int i = 1; i <= a[0]; ++i)
            for (int j = 1; j <= b.a[0]; ++j)
            {
                c.a[i + j - 1] += a[i] * b.a[j];
                if (c.a[i + j - 1] >= digit) c.a[i + j] += c.a[i + j - 1] / digit, c.a[i + j - 1] %= digit;
            }
        while (c.a[0] > 1 && c.a[c.a[0]] == 0) --c.a[0];
        return c;
    }
    
};
int main()
{
    
    return 0;
}
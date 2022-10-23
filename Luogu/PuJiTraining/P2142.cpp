#include <cstdio>
#include <cstring>
const int power = 100000000;
const int maxn = 2000;
class HP
{
private:
    int num[maxn];

public:
    HP()
    {
        memset(num, 0, sizeof(num));
        num[0] = 1;
    }
    HP(int a)
    {
        *this = a;
    }
    HP(char *s)
    {
        *this = s;
    }
    HP &operator=(char *s)
    {
        memset(num, 0, sizeof(num));
        int len = std::strlen(s), k = 1;
        num[0] = 1;
        for (int i = 1; i <= len; ++i)
        {
            if (k == power)
                k = 1, ++num[0];
            num[num[0]] += k * (s[len - i] ^ 48);
            k = (k << 1) + (k << 3);
        }
        return *this;
    }
    HP &operator=(int a)
    {
        memset(num, 0, sizeof(num));
        for (; a; a /= power)
            num[++num[0]] = a % power;
        return *this;
    }
    HP &operator=(const HP &b)
    {
        memcpy(num, b.num, sizeof(b.num));
    }
    bool operator>(const HP &b)
    {
        if (num[0] != b.num[0])
            return num[0] > b.num[0];
        for (int i = num[0]; i; --i)
            if (num[i] != b.num[i])
                return num[i] > b.num[i];
        return false;
    }
    bool operator<(const HP &b)
    {
        if (num[0] != b.num[0])
            return num[0] < b.num[0];
        for (int i = num[0]; i; --i)
            if (num[i] != b.num[i])
                return num[i] < b.num[i];
        return false;
    }
    bool operator<=(const HP &b)
    {
        return !(*this > b);
    }
    bool operator>=(const HP &b)
    {
        return !(*this < b);
    }
    bool operator==(const HP &b)
    {
        if (num[0] != b.num[0])
            return false;
        for (int i = num[0]; i; --i)
            if (num[i] != b.num[i])
                return false;
        return true;
    }
    HP &operator+=(const HP &b)
    {
        num[0] = (num[0] > b.num[0] ? num[0] : b.num[0]);
        for (int i = 1; i <= num[0]; ++i)
        {
            num[i] += b.num[i];
            if (num[i] >= power)
                num[i] -= power, ++num[i + 1];
        }
        if (num[num[0] + 1])
            ++num[0];
        return *this;
    }
    HP &operator+(const HP &b)
    {
        HP r = *this;
        r += b;
        return r;
    }
    HP &operator-=(const HP &b)
    {
        for (int i = 1; i <= num[0]; ++i)
        {
            num[i] -= b.num[i];
            if (num[i] < 0)
                --num[i + 1], num[i] += power;
        }
        while (!num[num[0]] && num[0] > 1)
            --num[0];
        return *this;
    }
    HP &operator-(const HP &b)
    {
        HP r = *this;
        r -= b;
        return r;
    }
    void output()
    {
        printf("%d", num[num[0]]);
        for (int i = num[0] - 1; i; --i)
            printf("%.8d", num[i]); //change when power changes
    }
};
char a1[11000], a2[11000];
int main()
{
    scanf("%s", a1);
    scanf("%s", a2);
    HP a = a1, b = a2;
    a += b;
    a.output();
    return 0;
}
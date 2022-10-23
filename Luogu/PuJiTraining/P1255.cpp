#include <cstdio>
#include <cstring>
const int power = 100000000;
const int maxn = 200;
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
    HP operator+(const HP &b)
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
    HP operator-(const HP &b)
    {
        HP r = *this;
        r -= b;
        return r;
    }
    HP operator*(const HP &b)
    {
        HP r;
        r.num[0] = num[0] + b.num[0] + 1;
        int i,j;
        for(i = 1;i<=num[0];++i)
            for(j = 1;j<=b.num[0];++j)
            {
                r.num[i+j-1] += num[i] * b.num[j];
                if(r.num[i+j-1] >= power)
                {
                    r.num[i+j] += r.num[i+j-1] / power;
                    r.num[i+j-1] %= power;
                }
            }
        while(!r.num[r.num[0]] && r.num[0] > 1)
            --r.num[0];
        return r;
    }
    HP &operator*=(const HP &b)
    {
        *this = (*this * b);
    }
    void output()
    {
        printf("%d", num[num[0]]);
        for (int i = num[0] - 1; i >= 1; --i)
            printf("%.8d", num[i]); //change when power changes
    }
};
HP a[3];
int n;
int main()
{
    scanf("%d",&n);
    a[2] = 2;a[1] = 1;
    for(int i = 3;i<=n;++i)
        a[i % 3] = a[(i-1)%3] + a[(i-2)%3];
    a[n%3].output();
    return 0;
}
#include <cstdio>

template <const unsigned int _MOD>
struct ModNum
{
    unsigned int x;
    ModNum(unsigned int t) : x(t)
    {
    }
    ModNum operator+(const ModNum& other)
    {
        unsigned int ret = this->x + other.x;
        if (ret >= _MOD) ret -= _MOD;
        return ModNum(ret);
    }
    ModNum& operator+=(const ModNum& other)
    {
        this->x += other.x;
        if (this->x >= _MOD) this->x -= _MOD;
        return *this;
    }
    ModNum operator-(const ModNum& other)
    {
        if (this->x < other.x) return ModNum(_MOD - other.x + this->x);
        return ModNum(this->x - other.x);
    }
    ModNum& operator-=(const ModNum& other)
    {
        if (this->x < other.x)
            this->x = _MOD - other.x + this->x;
        else
            this->x = this->x - other.x;
        return *this;
    }
    ModNum operator*(const ModNum& other)
    {
        unsigned long long ret = 1ll * this->x * other.x;
        if (ret >= _MOD) ret %= _MOD;
        return ModNum(ret);
    }
};
int main()
{
    ModNum<17> a(10), b(5);
    printf("%d\n", (a + b + b).x);
    printf("%d\n", (a * b).x);
    a += b;
    printf("%d\n", a.x);
    a -= b;
    printf("%d\n", a.x);
    return 0;
}
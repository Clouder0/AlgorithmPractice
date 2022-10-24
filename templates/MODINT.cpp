#include <cstdio>


// T supports long long/int
template <const unsigned int _MOD, typename T>
struct ModNum
{
    T x;
    ModNum() { x = 0; }
    template <typename _Tp>
    ModNum(_Tp t) : x(t)
    {
    }
    ModNum(const ModNum& other) : x(other.x) {}
    explicit operator T() const { return x; }
    ModNum& operator+=(const ModNum& other)
    {
        x += other.x;
        if (this->x >= _MOD) x -= _MOD;
        return *this;
    }
    ModNum& operator-=(const ModNum& other) { return *this += _MOD - other.x; }
    ModNum& operator*=(const ModNum& other)
    {
        unsigned long long ret = 1ll * x * other.x;
        if (ret >= _MOD) ret %= _MOD;
        this-> x = ret;
        return *this;
    }
   ModNum inv() const
    {
        T a = x, b = _MOD, u = 1, v = 0;
        while (b)
        {
            T t = a / b;
            a -= t * b; std::swap(a, b);
            u -= t * v; std::swap(u, v);
        }
        return ModNum(u);
    }
    ModNum& operator/=(const ModNum& other) { return *this *= other.inv(); }
    friend ModNum operator+(const ModNum& a, const ModNum& b) { return ModNum(a) += b; }
    friend ModNum operator-(const ModNum& a, const ModNum& b) { return ModNum(a) -= b; }
    friend ModNum operator*(const ModNum& a, const ModNum& b) { return ModNum(a) *= b; }
    friend ModNum operator/(const ModNum& a, const ModNum& b) { return ModNum(a) /= b; }
    bool operator==(const ModNum& other) { return x == other.x; }
    bool operator!=(const ModNum& other) { return x != other.x; }
    bool operator<(const ModNum& other) { return x < other.x; }
    bool operator>(const ModNum& other) { return x > other.x; }
    bool operator<=(const ModNum& other) { return x <= other.x; }
    bool operator>=(const ModNum& other) { return x >= other.x; }

    template <typename _Istream>
    friend _Istream& operator>>(_Istream& is, ModNum& self)
    {
        return is >> self.m_val;
    }
    template <typename _Ostream>
    friend _Ostream& operator<<(_Ostream& os, const ModNum& self)
    {
        return os << self.m_val;
    }
};
int main()
{
    ModNum<17, int> a(10), b(5);
    printf("%d\n", (a + b + b).x);
    printf("%d\n", (a * b).x);
    a += b;
    printf("%d\n", a.x);
    a -= b;
    printf("%d\n", a.x);
    return 0;
}
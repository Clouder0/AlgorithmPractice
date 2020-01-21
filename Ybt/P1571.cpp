#include <cstdio>
#include <cstring>
using namespace std;
template<typename T>
inline T read(T &r)
{
    static char c;r = 0;
    for(c = getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
    return r;
}
template<typename T>
inline T max(const T &a,const T &b){return a>b?a:b;}

const int power = 4;      //每次运算的位数为10的power次方，在这里定义为了方便程序实现
const int base = 10000;      //10的power次方。
 
 
//要压位的时候，只需改power 和 base即可，如压万位高精，那么power = 4, base = 10000
 
 
const int MAXL = 200;    //数组的长度。
 
 
char a[MAXL], b[MAXL];
struct num
{
    int a[MAXL];
    num() { memset(a, 0, sizeof(a)); }                      //初始化
    num(char *s)                                            //将一个字符串初始化为高精度数
    {
        memset(a, 0, sizeof(a));
        int len = strlen(s);
        a[0] = (len+power-1) / power;                       //数的长度
        for (int i=0, t=0, w; i < len ;w *= 10, ++i)        
        {
            if (i % power == 0) { w = 1, ++t; }
            a[t] += w * (s[i]-'0');
        }
        //初始化数组，这里自己模拟一下，应该很容易懂的~
    }
    num(int x)
    {
        memset(a,0,sizeof(a));
        for(a[0] = 0;x;a[++a[0]] = x % base,x /= base);
    }
    void add(int k) { if (k || a[0]) a[ ++a[0] ] = k; }     //在末尾添加一个数，除法的时候要用到
    void print()                                            //打印此高精度数
    {
        printf("%d", a[ a[0] ]);      
        //先打印最高位，为了压位 或者 该高精度数为0 考虑
        for (int i = a[0]-1;i > 0;--i)
        printf("%0*d", power, a[i]);  
        //这里"%0*d", power的意思是，必须输出power位，不够则前面用0补足
        printf("\n");
    }
};
 
 
bool operator < (const num &p, const num &q)              //判断小于关系，除法的时候有用
{
    if (p.a[0] < q.a[0]) return true;
    if (p.a[0] > q.a[0]) return false;
    for (int i = p.a[0];i > 0;--i)
    {
        if (p.a[i] != q.a[i]) return p.a[i] < q.a[i];
    }
    return false;
}
 
 
num operator + (const num &p, const num &q)               //加法，不用多说了吧，模拟一遍，很容易懂
{
    num c;
    c.a[0] = max(p.a[0], q.a[0]);
    for (int i = 1;i <= c.a[0];++i)
    {
        c.a[i] += p.a[i] + q.a[i];
        c.a[i+1] += c.a[i] / base;
        c.a[i] %= base;
    }
    if (c.a[ c.a[0]+1 ]) ++c.a[0];
    return c;
}
 
 
num operator - (const num &p, const num &q)               //减法，也不用多说，模拟一遍，很容易懂
{
    num c = p;
    for (int i = 1;i <= c.a[0];++i)
    {
        c.a[i] -= q.a[i];
        if (c.a[i] < 0) { c.a[i] += base; --c.a[i+1]; }
    }
    while (c.a[0] > 0 && !c.a[ c.a[0] ]) --c.a[0];          
    //我的习惯是如果该数为0，那么他的长度也是0，方便比较大小和在末尾添加数时的判断。
    return c;
}
 
 
num operator * (const num &p, const num &q)                 
//乘法，还是模拟一遍。。其实高精度就是模拟人工四则运算！
{
    num c;
    c.a[0] = p.a[0]+q.a[0]-1;
    for (int i = 1;i <= p.a[0];++i)
    for (int j = 1;j <= q.a[0];++j)
    {
        c.a[i+j-1] += p.a[i]*q.a[j];
        c.a[i+j] += c.a[i+j-1] / base;
        c.a[i+j-1] %= base;
    }
    if (c.a[ c.a[0]+1 ]) ++c.a[0];
    return c;
}
struct hp
{
    int num[200];
    hp()
    {
        memset(num,0,sizeof(num));
        num[0] = 1;
    }
    hp(int x) : hp()
    {
        for(num[0] = 0;x;num[++num[0]] = x % power,x /= power);
        if(num[0] < 1)
            num[0] = 1;
    }
    hp(const hp &b)
    {
        memcpy(num,b.num,sizeof(b.num));
    }
    hp operator+(const hp &b)
    {
        hp r(*this);
        int len = max(this->num[0],b.num[0]);
        for(int i = 1;i<=len;++i)
        {
            r.num[i] += b.num[i];
            if(r.num[i] > power)
                ++r.num[i+1],r.num[i] -= power;
        }
        r.num[0] = len;
        if(r.num[r.num[0]+1])
            ++r.num[0];
        return r;
    }
    bool operator<(const hp &b) const
    {
        if(this->num[0] != b.num[0])
            return this->num[0] < b.num[0];
        for(int i = num[0];i>=1;--i)
            if(this->num[i] != b.num[i])
                return this->num[i] < b.num[i];
            return false;
    }
    bool operator>(const hp &b) const
    {
        if(this->num[0] != b.num[0])
            return this->num[0] > b.num[0];
        for(int i = num[0];i>=1;--i)
            if(this->num[i] != b.num[i])
                return this->num[i] > b.num[i];
            return false;
    }
    hp operator*(const hp &b)
    {
        hp r;
        r.num[0] = num[0] + b.num[0] + 1;
        for(int i = 1;i<=this->num[0];++i)
            for(int j = 1;j<=b.num[0];++j)
            {
                r.num[i+j-1] += this->num[i] * b.num[j];
                if(r.num[i+j-1] >= power)
                    r.num[i+j] += r.num[i+j-1] / power,r.num[i+j-1] %= power;
            }
        while(r.num[r.num[0]] == 0 && r.num[0] > 1)
            --r.num[0];
        return r;
    }
    void output()
    {
        printf("%d",num[num[0]]);
        for(int i = num[0] - 1;i>=1;--i)
            printf("%4d",num[i]);
    }
};
int n;
num w[100];
num dp[100][100];
template<typename T>
inline T min(const T &a,const T &b)
{
    return a<b?a:b;
}
int main()
{
    read(n);
    int temp;
    for(int i = 1;i<=n;++i)
        w[i] = read(temp);
    for(int i = 1;i<=n;++i)
        for(int j = 1;j<=n;++j)
            dp[i][j].a[0] = 199;
    for(int i = 1;i<=n;++i)
        dp[i][i] = w[i],dp[i][i+1] = 0;
    for (int k = 1; k <= n; ++k)
        for (int i = 1; i + k<= n; ++i)
            for (int j = i; j <= i + k; ++j)
                dp[i][i+k] = min(dp[i][i+k],dp[i][j] + dp[j][i+k] + w[i]*w[j]*w[i+k]);
    dp[1][n].print();
    return 0;
}
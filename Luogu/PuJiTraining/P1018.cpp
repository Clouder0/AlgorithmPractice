// luogu-judger-enable-o2
#include <iostream>
#include <string>
#include <iterator>
#include <cstring>
using namespace std;
const int maxl = 500;
struct BigNum
{
    int all[maxl + 1];
    short length = 0;
    void UpdateLength()
    {
        length = maxl;
        while (length >= 0 && all[length] == 0)
            --length;
        ++length;
    }
    void LMove(int i)
    {
        memmove(all + i, all, sizeof(int) * length);
        memset(all, 0, sizeof(int) * i);
        length += i;
    }
    BigNum operator+(const BigNum &b)
    {
        BigNum result(b);
        for (int i = 0; i < length; i++)
        {
            result.all[i] += all[i];
            result.all[i + 1] += result.all[i] / 10;
            result.all[i] %= 10;
        }
        result.UpdateLength();
        return result;
    }
    BigNum operator*(const BigNum &b)
    {
        BigNum result;
        BigNum temp;
        for (int i = 0; i < length; i++)
        {
            temp = b;
            for (int j = 0; j < temp.length; j++)
                temp.all[j] *= all[i];
            for (int j = 0; j <= temp.length; j++)
            {
                temp.all[j + 1] += temp.all[j] / 10;
                temp.all[j] %= 10;
            }
            temp.UpdateLength();
            temp.LMove(i);
            result = result + temp;
        }
        result.UpdateLength();
        return result;
    }
    BigNum()
    {
        memset(all, 0, sizeof(all));
    }
    BigNum(const BigNum &a)
    {
        length = a.length;
        memmove(all, a.all, sizeof(all));
        UpdateLength();
    }
    BigNum(string s)
    {
        string::reverse_iterator it = s.rbegin();
        while (it != s.rend())
            all[length++] = *it++ - '0';
        memset(all + length, 0, sizeof(int) * (maxl - length + 1));
    }
    void print()
    {
        for (int i = length - 1; i >= 0; i--)
            cout << all[i];
    }
    bool operator>(const BigNum &b) const
    {
        if (length != b.length)
            return length > b.length;
        for (int i = length - 1; i >= 0; i--)
            if (all[i] != b.all[i])
                return all[i] > b.all[i];
        return false;
    }
};
BigNum max(const BigNum &a, const BigNum &b)
{
    return a > b ? a : b;
}
BigNum dp[50][10]; //dp[i][j]代表在前j个数字中插入了i个乘号的最大情况
int n, k;
string s;
int main()
{
    cin >> n >> k >> s;
    for (int i = 1; i <= n; i++)
        dp[i][0] = BigNum(s.substr(0, i));
    for(int i = 1;i<=n;++i)
        for(int j = 1;j<=k;++j)
            for(int p = 1;p<i;++p)
            {
                BigNum t = dp[p][j-1] * BigNum(s.substr(p,i-p));
                t.UpdateLength();
                dp[i][j].UpdateLength();
                if(t > dp[i][j])
                {
                     //printf("dp[%d][%d] from dp[%d][%d],string: %s,oldvalue:",i,j,p,j-1,s.substr(p,i-p).c_str());
                     //dp[i][j].print();
                     //printf(",newvalue:");
                     dp[i][j] = t;
                     //t.print(),putchar('\n');   
                }
            }
//    for(int i = 1;i<=n;++i)
  //      for(int j = 0;j<=k;++j) printf("dp[%d][%d]:",i,j),dp[i][j].print(),putchar('\n');
    for(int i = 0;i<=dp[n][k].length;++i)
        dp[n][k].all[i + 1] += dp[n][k].all[i] / 10,dp[n][k].all[i] %= 10;
    dp[n][k].UpdateLength();
    dp[n][k].print();
    return 0;
}
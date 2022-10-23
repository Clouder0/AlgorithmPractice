#include <cstdio>
#include <queue>
#include <map>
using namespace std;
template<typename T>
inline void _swap(T &a,T &b)
{
    T t = a;
    a = b;
    b = t;
}
const int target = 123804765;
queue<pair<int,int> > q;
map<int,int> mp;
int s;
int temp[4][4];
inline int getS()
{
    int res = 0;
    for(int i = 1;i<=3;++i)
        for(int j = 1;j<=3;++j)
            res = res * 10 + temp[i][j];
    return res;
}
int main()
{
    scanf("%d",&s);
    q.push(make_pair(s,0));
    while(!q.empty())
    {
        int u = q.front().first;
        int step = q.front().second;
        q.pop();
        if(u == target)
        {
            printf("%d",step);
            return 0;
        }
        if(mp.find(u) != mp.end())
            continue;
        mp[u] = step;
        int p = 9;
        while(p)
        {
            temp[((p-1)/3)+1][((p+2)%3)+1] = u % 10;
            u /= 10;
            --p;
        }
        for(int i = 1;i<=3;++i)
            for(int j = 1;j<=3;++j)
                if(temp[i][j] == 0)
                {
                    if(i != 1)
                    {
                        _swap(temp[i][j],temp[i-1][j]);
                        q.push(make_pair(getS(),step + 1));
                        _swap(temp[i][j],temp[i-1][j]);
                    }
                    if(i != 3)
                    {
                        _swap(temp[i][j],temp[i+1][j]);
                        q.push(make_pair(getS(),step + 1));
                        _swap(temp[i][j],temp[i+1][j]);
                    }
                    if(j != 1)
                    {
                        _swap(temp[i][j],temp[i][j-1]);
                        q.push(make_pair(getS(),step + 1));
                        _swap(temp[i][j],temp[i][j-1]);
                    }
                    if(j != 3)
                    {
                        _swap(temp[i][j],temp[i][j+1]);
                        q.push(make_pair(getS(),step + 1));
                        _swap(temp[i][j],temp[i][j+1]);
                    }
                }
    }
    return 0;
}
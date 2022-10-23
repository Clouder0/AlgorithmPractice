#include <cstdio>
using namespace std;
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
int n,a,b;
int origin[1010][1010];
int minn[1010][1010],maxx[1010][1010];
int que[1010],qtail,qhead;
int main()
{
    read(a);
    read(b);
    read(n);
    for(int i = 1;i<=a;++i)
        for(int j = 1;j<=b;++j)
            read(origin[i][j]);
    for(int i = 1;i<=a;++i)
    {
        que[1] = 1,qtail = 1,qhead = 1;
        for(int j = 2;j<=b;++j)
        {
            while (origin[i][que[qtail]] >= origin[i][j] && qtail >= qhead)
                --qtail;
            que[++qtail] = j;
            while (j - que[qhead] + 1 > n)
                ++qhead;
            if(j >= n)
                minn[i][j-n+1] = origin[i][que[qhead]];
        }
        que[1] = 1, qtail = 1, qhead = 1;
        for (int j = 2; j <= b; ++j)
        {
            while (origin[i][que[qtail]] <= origin[i][j] && qtail >= qhead)
                --qtail;
            que[++qtail] = j;
            while (j - que[qhead] + 1 > n)
                ++qhead;
            if(j >= n)
                maxx[i][j-n+1] = origin[i][que[qhead]];
        }
    }
    for(int i = 1;i<=b-n+1;++i)
    {
        que[1] = 1,qtail = 1,qhead = 1;
        for(int j = 2;j<=a;++j)
        {
            while(maxx[que[qtail]][i] <= maxx[j][i] && qtail >= qhead)
                --qtail;
            que[++qtail] = j;
            while(j - que[qhead] + 1 > n)
                ++qhead;
            if(j >= n)
                maxx[j-n+1][i] = maxx[que[qhead]][i];
        }
        que[1] = 1, qtail = 1, qhead = 1;
        for (int j = 2; j <= a; ++j)
        {
            while(minn[que[qtail]][i] >= minn[j][i] && qtail >= qhead)
                --qtail;
            que[++qtail] = j;
            while(j - que[qhead] + 1 > n)
                ++qhead;
            if(j >= n)
                minn[j-n+1][i] = minn[que[qhead]][i];
        }
    }
    int ans = 1<<30;
    for(int i = 1;i<=a - n + 1;++i)
        for(int j = 1;j<=b - n + 1;++j)
            ans = ans > maxx[i][j] - minn[i][j] ? maxx[i][j] - minn[i][j] : ans;
    printf("%d",ans);
    return 0;
}
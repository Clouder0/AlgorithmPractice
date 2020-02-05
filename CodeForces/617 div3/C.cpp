    #include <cstdio>
    using namespace std;
    template<typename T>
    void read(T &r)
    {
        static char c;r=0;
        for(c=getchar();c>'9'||c<'0';c=getchar());
        for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
    }
    const int maxn = 2e5 + 10;
    int T;
    int n;
    int xsum[maxn],ysum[maxn];
    char s[maxn];
    int main()
    {
        read(T);
        while(T--)
        {
            read(n);
            scanf("%s",s+1);
            for(int i = 1;i<=n;++i)
            {
                xsum[i] = xsum[i-1];
                ysum[i] = ysum[i-1];
                switch(s[i])
                {
                    case 'L':
                        xsum[i]--;
                        break;
                    case 'R':
                        xsum[i]++;
                        break;
                    case 'U':
                        ysum[i]++;
                        break;
                    case 'D':
                        ysum[i]--;
                        break;
                }
            }
            for(int len = 1;len<=n;++len)
            {
                for(int l = 1,r = l + len - 1;r<=n;++l,++r)
                {
                    if(xsum[r] - xsum[l-1] == 0 && ysum[r] - ysum[l-1] == 0)
                    {
                        printf("%d %d\n",l,r);
                        goto end;
                    }
                }
            }
            puts("-1");
            end:;
        }
        return 0;
    }
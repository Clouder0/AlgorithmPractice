#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 300,maxm = 1e6;
char s[maxn];
int n, A, B;
int minn[maxn][maxn],maxx[maxn][maxn];
int main()
{
    scanf("%d %d %d",&n,&A,&B);
    for (int i = 1; i <= n; ++i) 
    {
        scanf("%s",s + 1);
        for (int j = 1; j <= n; ++j)
            if (s[j] == '-') maxx[i][j] = -1, minn[i][j] = -2;
            else if (s[j] == '+') maxx[i][j] = 2, minn[i][j] = 1;
            else if(s[j] == '=' || i == j) minn[i][j] = maxx[i][j] = 0;
            else minn[i][j] = -2,maxx[i][j] = 2;
    }
//    for (int i = 1; i <= n; ++i) maxx[i][i] = minn[i][i] = 0;
    for (int k = 1; k <= n; ++k)
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j)
                minn[i][j] = max(minn[i][j], minn[i][k] + minn[k][j]);
    for (int k = 1; k <= n; ++k)
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j)
                maxx[i][j] = min(maxx[i][j], maxx[i][k] + maxx[k][j]);
    /*
    for (int i = 1; i <= n; puts(""), ++i)
        for (int j = 1; j <= n; ++j) printf("%d ", minn[i][j]);
    for (int i = 1; i <= n; puts(""), ++i)
        for (int j = 1; j <= n; ++j) printf("%d ", maxx[i][j]);
    */
    int c1 = 0, c2 = 0, c3 = 0;
    for (int C = 1; C <= n; ++C)
        for (int D = C + 1; D <= n; ++D)
        {
            if (A == C || A == D || B == C || B == D) continue;
            if (minn[A][C] > maxx[D][B] || minn[A][D] > maxx[C][B]) ++c1;
            else if ((minn[A][C] == maxx[A][C] && minn[D][B] == maxx[D][B] && minn[A][C] == minn[D][B]) ||
                (minn[A][D] == maxx[A][D] && minn[C][B] == maxx[C][B] && minn[A][D] == minn[C][B])) ++c2;
            else if (maxx[A][C] < minn[D][B] || maxx[A][D] < minn[C][B]) ++c3;
        }
    printf("%d %d %d\n",c1,c2,c3);
    return 0;
}
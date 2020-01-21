# Description
The map of the capital of Berland can be viewed on the infinite coordinate plane. Each point with integer coordinates contains a building, and there are streets connecting every building to four neighbouring buildings. All streets are parallel to the coordinate axes.

The main school of the capital is located in $(sx,sy)$. There are n students attending this school, the i-th of them lives in the house located in (xi,yi). It is possible that some students live in the same house, but no student lives in $(sx,sy)$.

After classes end, each student walks from the school to his house along one of the shortest paths. So the distance the $i$-th student goes from the school to his house is $|s_x−x_i|+|s_y−y_i|$.

The Provision Department of Berland has decided to open a shawarma tent somewhere in the capital (at some point with integer coordinates). It is considered that the $i$-th student will buy a shawarma if at least one of the shortest paths from the school to the $i$
-th student's house goes through the point where the shawarma tent is located. It is forbidden to place the shawarma tent at the point where the school is located, but the coordinates of the shawarma tent may coincide with the coordinates of the house of some student (or even multiple students).

You want to find the maximum possible number of students buying shawarma and the optimal location for the tent itself.
## Input
The first line contains three integers $n$, $sx$, $sy (1≤n≤200000, 0≤sx,sy≤10^9)$ — the number of students and the coordinates of the school, respectively.

Then $n$ lines follow. The $i$-th of them contains two integers $xi, yi (0≤x_i,y_i≤10^9)$ — the location of the house where the $i$-th student lives. Some locations of houses may coincide, but no student lives in the same location where the school is situated.
## Output
The output should consist of two lines. The first of them should contain one integer $c$ — the maximum number of students that will buy shawarmas at the tent.

The second line should contain two integers $p_x$ and $p_y$ — the coordinates where the tent should be located. If there are multiple answers, print any of them. Note that each of $p_x$ and $p_y$ should be not less than $0$ and not greater than $10^9$.
# 题意
给定原点和若干点，定义点到原点距离为$|s_x−x_i|+|s_y−y_i|$，现在要选择一个位置建造帐篷，若一个点到原点有经过这个帐篷的最短路径，那么就会产生$1$点贡献。问在哪里建造帐篷能获得的贡献值最大。
# 思路
很显然，一个点到原点的最短路径可行方案覆盖了以该点和原点为对角顶点的整个矩形。
![Example](https://img-blog.csdnimg.cn/20191217150600230.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L01pc3NpbmdfQ2xvdWQ=,size_16,color_FFFFFF,t_70)
大概就是这样的一个矩形。因此我有了一个很自然的思路：每次给这个矩形里所有值+1，最后统计答案遍历每个点即可。
打算二维树状数组搞一搞，然后发现值域过大……
正解：这个矩形的某一个顶点是确定的，即原点是确定的，那么一定只有这几种情况：
1. 点在原点的左上方，那么建筑在原点左一格和原点上一格都可以让该点产生贡献。
2. 点在原点的左下方，那么建筑在原点左一格和原点下一格都可以让该点产生贡献。
3. 点在原点的右上方，那么建筑在原点右一格和原点上一格都可以让该点产生贡献。
4. 点在原点右下方，那么建筑在原点右一格和原点下一格都可以让该点产生贡献。
也就是说，原点上下左右四个建筑位置一定是最优的。
归纳一下，得到：
>原点左边的所有点都会对建筑在原点左一格的情况产生贡献。
>原点右边的所有点都会对建筑在原点右一格的情况产生贡献。
>原点上方的所有点都会对建筑在原点上一格的情况产生贡献。
>原点下方的所有点都会对建筑在原点上一格的情况产生贡献。
>
![example2](https://img-blog.csdnimg.cn/20191217151240702.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L01pc3NpbmdfQ2xvdWQ=,size_16,color_FFFFFF,t_70)
在其他位置建筑的话，肯定都不如这四个点，可以画一下贡献区域感受一下。
# Code
~~~cpp
#include <cstdio>
using namespace std;
inline char nc()
{
    static char buf[1000000],*p1 = buf,*p2 = buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++;
}
template<typename T>
void read(T &r)
{
    static char c; r=0;
    for(c=nc();c>'9'||c<'0';c=nc());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=nc());
}
int n,p,q;
int l,r,top,bottom;
inline int max(const int &a,const int &b){return a>b?a:b;}
int main()
{
    read(n);
    read(p);
    read(q);
    int x,y;
    for(;n;--n)
    {
        read(x);
        read(y);
        if(x < p)
            ++l;
        else if(x > p)
            ++r;
        if(y > q)
            ++top;
        else if(y < q)
            ++bottom;
    }
    int maxx = max(l,max(r,max(top,bottom)));
    printf("%d\n",maxx);
    if(maxx == l)
        printf("%d %d",p - 1,q);
    else if(maxx == r)
        printf("%d %d",p + 1,q);
    else if(maxx == top)
        printf("%d %d",p,q+1);
    else
        printf("%d %d",p,q-1);
    return 0;
}
~~~
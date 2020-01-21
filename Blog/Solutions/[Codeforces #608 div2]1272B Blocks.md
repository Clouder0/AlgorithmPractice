# Description
There are $n$ blocks arranged in a row and numbered from left to right, starting from one. Each block is either black or white.

You may perform the following operation zero or more times: choose two adjacent blocks and invert their colors (white block becomes black, and vice versa).

You want to find a sequence of operations, such that they make all the blocks having the same color. You don't have to minimize the number of operations, but it should not exceed $3⋅n$. If it is impossible to find such a sequence of operations, you need to report it.

## Input
The first line contains one integer $n(2≤n≤200)$ — the number of blocks.

The second line contains one string s consisting of n characters, each character is either "W" or "B". If the i-th character is "W", then the i-th block is white. If the i-th character is "B", then the i-th block is black.
## Output
If it is impossible to make all the blocks having the same color, print $−1$.
Otherwise, print an integer $k(0≤k≤3⋅n)$ — the number of operations. Then print $k$ integers $p_1,p_2,…,p_k (1≤p_j≤n−1)$, where $p_j$ is the position of the left block in the pair of blocks that should be affected by the $j$-th operation.
If there are multiple answers, print any of them.
# 题意
给定一串黑白文本，每次可以将其中相邻2个颜色翻转，求一个可行的操作序列使得操作后颜色相同。
如果不能找到输出-1
# 思路
一开始看到$n<=200$直接打了一发爆搜+记忆化，然后MLE炸到飞起……
正解是假定操作后全白，从头扫到尾一次，假定全黑，从头扫到尾一次，看看能否成功。
比如：我们要全白，而此时颜色是 黑白黑黑黑
可以将黑视作高台阶，白视作低台阶，然后一路推过去，最后能推平就可以了。
![例子](https://img-blog.csdnimg.cn/20191217144832648.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L01pc3NpbmdfQ2xvdWQ=,size_16,color_FFFFFF,t_70)
推平位置1后，往后找到位置2，推平位置2后，2 3都平了，再往后遍历找到位置4，推平位置4后，全部推平，合法。
因此操作序列就为：1 2 4
显然这样操作只会有2种结果：全平或者最后一个不平。
全黑全白两个都扫一遍就好了，复杂度$O(n)$
# Code
~~~cpp
#include <cstdio>
#include <cstring>
using namespace std;
int n,len;
char all[201];
char temp[201];
int path[201];
int tot;
bool checkblack()
{
    memcpy(temp,all,sizeof(all));
    tot = 0;
    for(int i = 1;i<len;++i)
    {
        if(temp[i] == 'W')
        {
            temp[i] = 'B';
            temp[i+1] = (temp[i+1] == 'W' ? 'B' : 'W');
            path[++tot] = i;
        }
    }
    return temp[len] == 'B';
}
bool checkwhite()
{
    memcpy(temp,all,sizeof(all));
    tot = 0;
    for(int i = 1;i<len;++i)
    {
        if(temp[i] == 'B')
        {
            temp[i] = 'W';
            temp[i+1] = (temp[i+1] == 'W' ? 'B' : 'W');
            path[++tot] = i;
        }
    }
    return temp[len] == 'W';
}
int main()
{
    scanf("%d",&n);
    scanf("%s",all+1);
    len = strlen(all+1);
    if(checkblack() || checkwhite())
    {
        printf("%d\n",tot);
        for(int i =1 ;i<=tot;++i)
            printf("%d ",path[i]);
    }
    else
        printf("-1");
    return 0;
}
~~~
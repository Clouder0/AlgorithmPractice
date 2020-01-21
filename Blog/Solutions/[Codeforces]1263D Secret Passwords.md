# 题目
One unknown hacker wants to get the admin's password of AtForces testing system, to get problems from the next contest. To achieve that, he sneaked into the administrator's office and stole a piece of paper with a list of $n$ passwords — strings, consists of small Latin letters.

Hacker went home and started preparing to hack AtForces. He found that the system contains only passwords from the stolen list and that the system determines the equivalence of the passwords $a$ and $b$ as follows:

two passwords $a$ and $b$ are equivalent if there is a letter, that exists in both $a$ and $b$;
two passwords $a$ and $b$ are equivalent if there is a password $c$ from the list, which is equivalent to both $a$ and $b$. 

If a password is set in the system and an equivalent one is applied to access the system, then the user is accessed into the system.

For example, if the list contain passwords "a", "b", "ab", "d", then passwords "a", "b", "ab" are equivalent to each other, but the password "d" is not equivalent to any other password from list. In other words, if:

    admin's password is "b", then you can access to system by using any of this passwords: "a", "b", "ab";
    admin's password is "d", then you can access to system by using only "d". 

**Only one** password from the list is the admin's password from the testing system. Help hacker to calculate the minimal number of passwords, required to **guaranteed** access to the system. Keep in mind that the hacker does not know which password is set in the system.
# 输入
The first line contain integer $n (1≤n≤2\times 10^5)$ — number of passwords in the list. Next n lines contains passwords from the list – non-empty strings $s_i$, with length at most $50$letters. Some of the passwords may be equal.

It is guaranteed that the total length of all passwords does not exceed $10^6$ letters. All of them consist only of lowercase Latin letters.
# 输出
In a single line print the minimal number of passwords, the use of which will allow **guaranteed** to access the system.
# 题目大意
给定$n$个单词，单词全由小写字母构成，保证每个单词不超过$50$个字母，总长度不超过$10^6$个字母。
两个单词是等效的，当且仅当：

1. 两个单词中有任一字母相等。
2. 存在一中间单词，使得两个单词都与中间单词相等。

即：
$a = c,b = c$，则有$a=b$。
# 思路
显然等效的单词是一个集合，容易想到用并查集维护，那么最后答案就是集合个数。
但如何维护就成了问题。
发现其实所有操作都在考虑字母，因此可以直接维护字母的并查集，而每个单词就是一个集合，因此每次读入单词时将单词内所有字母合并到一个集合中。
但还需要考虑没有出现的字母，遍历单词时记录一下即可。
复杂度$O(n),n≤10^6$
# 代码
```cpp
#include <cstdio>
#include <cstring>
using namespace std;
int fa[27], vis[27];
inline int find(const int &x)
{
    return fa[x] == x ? x : fa[x] = find(fa[x]);
}
inline void unite(const int &a, const int &b)
{
    int t1 = find(a), t2 = find(b);
    if (t1 == t2)
        return;
    fa[t1] = t2;
}
char all[60];
int n, len,ans;
inline char nc()
{
    static char buf[1050000],*p1 = buf,*p2 = buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,1050000,stdin),p1==p2)?EOF:*p1++;
}
void read(char *s)
{
    static char c;
    for(c=nc();c>'z'||c<'a';c=nc());
    for(;c>='a'&&c<='z';*(++s) = c,c=nc());
    *(++s) = '\0';//快读的细节，为了防止上次读入内容影响到，要加文本终止符
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= 26; ++i)
        fa[i] = i;//初始化
    for (int i = 1; i <= n; ++i)
    {
        read(all);
        len = strlen(all + 1);
        for (int j = 1; j <= len; ++j)
            unite(all[j] - 'a' + 1, all[1] - 'a' + 1), vis[all[j] - 'a' + 1] = 1;
    }
    for(int i = 1;i<=26;++i)
        if(vis[i] && find(i) == i)
            ++ans;
    printf("%d",ans);
    return 0;
}
```


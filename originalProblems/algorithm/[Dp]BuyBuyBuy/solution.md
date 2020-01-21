# Solution
Codeforces的原题，简单说一下解法。
记录一个sum，从头开始将每个数加入sum中，而不加最后一个数。
如果过程中sum有<0的话，那么小B一定可以去掉这一段<0的区间而取后面的，相当于消除了一个负面影响，那么输出“No！”
从尾部也扫一遍，即可解决问题。
时间复杂度$O(n)$。

[原题链接](https://codeforces.com/contest/1285/problem/B)
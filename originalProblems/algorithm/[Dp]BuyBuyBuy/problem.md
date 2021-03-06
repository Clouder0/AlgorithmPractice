# Title: 买买买(BuyBuyBuy)

# Backgroud

中国人过节总是有买东西的习俗，各大商家也都看准时机宰人。  
现在有两个聪明的小孩要买东西了，他们有着各自的“聪明的”购买策略，并且为孰优孰劣争执不休。  
他们决定实践出真知，于是他们走进了商场。当然，其中更“聪明”的小孩决定不打无准备之仗，于是找你求助。

# Description

小A总是会盲目地买下所有的商品。  
小B则会主观地选择购买区间$[l,r]$中的所有商品，当然，为了和小A区别开，这个区间不能包含所有商品。  
现在小A要问你，他买下的商品的价值**在任意情况下**能否**严格大于**小B买下的商品的价值。

# Input Format

第一行给出一个整数$T$，$1 \leq T \leq 100$，代表数据组数。
对于每组数据:
第一行给出一个整数$n$，($1 \leq n \leq 100000$)，代表商品总数。
第二行给出$n$个整数，代表每个商品的价值量。保证该数在$[-10000,10000]$的区间内。

# Output Format

输出`Just do it!`代表小A始终获胜。
否则输出`What a Shame!`。

# Test Cases

# Case 1
### Input
```
3
4
1 2 3 4
3
7 4 -1
3
5 -5 5
```

### Output
```
Just do it!
What a Shame!
What a Shame!
```
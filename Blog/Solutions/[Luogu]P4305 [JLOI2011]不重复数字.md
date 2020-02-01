# Solution

题目意思相当清楚了，只保留第一次出现的数，那么可以：  
在新的数出现时判断是否出现过，若出现过则不输出。  

而判断是否重复，可以使用map或hashtable。  
然而map的单次查询复杂度是$O(logn)$，在此题中总复杂度会达到$O(Tnlogn)$，经过计算后最大会达到$4 \times 10^7$的大小。  
虽然理论上是可以通过的，但实际上并不能……可能是常数过大的缘故。  
因此只能使用hashtable了。  

如果不想手写hashtable，可以使用c++11提供的unordered_map，或者pb_ds库中的hash_table。  
其中c++11在NOIP中似乎是不被支持的，而pb_ds库能否使用依然未有定论。  
我使用了pb_ds库中的hashtable。
定义方法：
```cpp
cc_hash_table<string,int>mp1;//拉链法
gp_hash_table<string,int>mp2;//查探法(快一些)
```
拉链法即在冲突时建立链表，而探查法则是在冲突时使用特定方法计算得出新的地址再访问。  
具体实现不深究了。  

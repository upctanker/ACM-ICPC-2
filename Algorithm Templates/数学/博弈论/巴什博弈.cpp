巴什博弈

典型问题：一堆只有n个物品，两人轮流从堆中取，最少一个，最多m个，最后取光者胜。

如果n=m+1。后手胜。取胜法则n=(m+1)*r+s。其中r为任意自然数，s<=m。
若s不为0则先手胜，因为先手总会给后手留下(m+1)倍数个。

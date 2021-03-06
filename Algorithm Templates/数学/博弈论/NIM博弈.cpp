尼姆博弈

典型问题：有n堆若干物品，两人轮流从某一堆取任意多物品，规定每次至少取一个，多者不限，最后取光者胜。

以三堆为例，我们用（a，b，c）表示某种局势，首先（0，0，0）显然是必败态。第二 种必败态是（0，n，n），先手在某一堆中拿走k个（k<n），不论k为多少，

后手只要在另一堆中拿走k个物品，先手总会面临（0，0，0）的情况。

对于判断奇异局势（必败局势），这里要用到异或运算，运算符（+）。

任何奇异局势（a，b，c）都有a（+）b（+）c =0。

注意到异或运算的交换律和结合律，及a（+）a=0，:

a（+）b（+）(a（+）b)=(a（+）a)（+）(b（+）b)=0（+）0=0。



从一个非奇异局势向一个奇异局势转换的方式可以是：

1）使 a = c（+）b

2）使 b = a（+）c

3）使 c = a（+）b

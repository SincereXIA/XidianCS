![在这里插入图片描述](https://img-blog.csdnimg.cn/20200714155949812.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MzYyNzU2MQ==,size_16,color_FFFFFF,t_70)
指令周期 是一个指令所需时间
指令周期可分为 CPU周期/机器周期

CPU周期是由多个微操作组成，控制位操作的指令叫做微命令

节拍周期是一个微操作

# 取指
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200714195253195.png)
# 中断
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200714195345335.png)
# 执行
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200714165451552.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MzYyNzU2MQ==,size_16,color_FFFFFF,t_70)
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200714165510546.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MzYyNzU2MQ==,size_16,color_FFFFFF,t_70)
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200714165607234.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MzYyNzU2MQ==,size_16,color_FFFFFF,t_70)
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200714165620966.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MzYyNzU2MQ==,size_16,color_FFFFFF,t_70)

# 控制器
## 硬布线
看成顺序逻辑电路
 
一级时序：只有节拍
二级时序：有CPU周期 节拍

RISC主要使用硬布线

## 微程序
把一个指令的微指令序列存在一个程序中
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200714211407283.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MzYyNzU2MQ==,size_16,color_FFFFFF,t_70)
微指令 地址+控制

地址：1）双地址：下一地址，跳转地址 2）单地址 3）可变
控制：1）水平型 字段译码法 把互斥的放在一段 2）垂直型
CISC主要采用微程序

控制存储器容量=微指令长度×微程序中微指令数×指令数

# 性能
CPU时间

CPI每条指令所用时间数

MIPS 每秒执行百万指令数

FLOPS 每秒浮点数计算次数
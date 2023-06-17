利用总线把计算机各模块连接在一起

总线带宽：每秒传输字节数
总线宽度：总线线数

# 总线仲裁
集中式仲裁
## 菊花链
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200715111423972.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MzYyNzU2MQ==,size_16,color_FFFFFF,t_70)
## 轮询
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200715111442530.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MzYyNzU2MQ==,size_16,color_FFFFFF,t_70)
## 独立请求
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200715111509226.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MzYyNzU2MQ==,size_16,color_FFFFFF,t_70)
分布式仲裁

## 自举分布式
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200715111954205.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MzYyNzU2MQ==,size_16,color_FFFFFF,t_70)
## 链式分布式
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200715112017587.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MzYyNzU2MQ==,size_16,color_FFFFFF,t_70)
# IO接口
把IO设备连接到总线上
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200715112438293.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MzYyNzU2MQ==,size_16,color_FFFFFF,t_70)
编址方式
存储器映射：统一编址
IO映射方式：独立编址

# IO技术
## 程序查询
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200715112925736.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MzYyNzU2MQ==,size_16,color_FFFFFF,t_70)
## 中断
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200715113119708.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MzYyNzU2MQ==,size_16,color_FFFFFF,t_70)
## DMA
由DMA控制器完成IO操作
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200715145050275.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MzYyNzU2MQ==,size_16,color_FFFFFF,t_70)
## IO通道
IO通道是DMA拓展，核心是IOP

选择通道：只选择一个高速设备
数组多路通道
字节多路通道
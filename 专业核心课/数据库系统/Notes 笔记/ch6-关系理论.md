# 关系数据库理论

> **关系的外延和内涵**
>
> - **外延：关系模型的值**，即关系模型中的数据，称为关系、实例或当前值。它随着时间的推移而变化，主要由元组的插入、删除和修改而引起。**外延是动态的**。
> - **内涵：是对关系、属性、域的定义和说明，即关系模型的型的定义。**内涵是静态的。
> - 关系模式通常简记为：R <U，F>。

## 关系模式的存储异常

- **数据冗余大**
- **修改异常**
- **插入异常**
- **删除异常**

## 规范化

- 函数依赖

  - 非平凡函数依赖：依赖且不包含
  - 平凡函数依赖：依赖且包含
  - 相互决定：相互依赖
  - 完全函数依赖：对 X->Y 中 X 的任何一个真子集，都不能决定 Y
  - 传递函数依赖

- 多值依赖

  > 在关系模式R(X,Y,Z)的任一关系r中，如果存在元组t, s，使得t[X] = s[X]，就必然存在元组 w,
  > v 属于r，使得 w[X] = v[X] = t[X]  (= s[X])，而 w[Y] = t[Y], w[Z] = s[Z] ；v[Y] = s[Y]，v[Z] = t[Z] （即交换 t, s 在Z上的分量构成的新元组必然在r中），则称Y多值依赖于X，记为X->->Y。
  >
  > ![mark](http://media.sumblog.cn/blog/20181230/3ROk0u02Y3mW.png?imageMogr2/thumbnail/!50p)
  >
  > - 平凡的多值依赖：Z为空集（函数依赖）

### 范式

- 1NF：

  关系模式R的所有属性都是不可分的基本数据项。

  第一范式是对关系模式的最起码的要求。不满足第一范式的数据库模式不能称为关系数据库。(由关系属性的原子性得出)。

- 2NF：

  每一个非主属性都完全函数依赖于R的码 **消除了非主属性部分依赖**

- 3NF：

  **不含纯粹的非主属性对码的传递依赖**，

  ![mark](http://media.sumblog.cn/blog/20181230/FdWqzNTLQgce.png?imageMogr2/thumbnail/!50p)

- BCNF

  不存在非主属性对非码的函数依赖，每一个函数依赖的决定因素都 **包含码**

  **排除了任何属性对码的传递依赖和部分依赖**

  - R中所有非主属性对每一个码都完全函数依赖。
  - R中所有主属性对每个不包含它的码都完全函数依赖。
  - R中没有任何属性完全函数依赖于非码的任何一组属性。

  **如果只有一个码，且不存在传递和部分依赖，那么其一定属于 BCNF**

  ![mark](http://media.sumblog.cn/blog/20181230/x36U77xRAWTH.png?imageMogr2/thumbnail/!60p)

- 4NF

  **不存在非平凡的多值依赖**

## 数据依赖的公理系统

### Armstrong 公理系统

==自反律、增广律、传递率，可以推理出 合并、分解、伪传递==

#### 属性集的闭包

属性集 X 关于**函数依赖集 F 的闭包：** $X_F^+$

![mark](http://media.sumblog.cn/blog/20181230/BGCo2QOViQgg.png?imageMogr2/thumbnail/!60p)

#### 最小函数依赖集

- 函数依赖集等价
  $$
  F^+=G^+ 当且仅当 F\subseteq G^+ 且 G\subseteq F^+
  $$

- 最小依赖集的定义

  - **==右部单：==** F 中任一函数依赖的右部仅含有一个属性 
  - **==左部最小化：==** 如果 $(X-B)\to A$ 就不要 $X\to A$
  - **==无冗余==**（去掉多余的函数依赖）

- **最小依赖集的求解算法**

  ![mark](http://media.sumblog.cn/blog/20181230/ei7fOdhbqove.png?imageMogr2/thumbnail/!60p)

  ![mark](http://media.sumblog.cn/blog/20181230/g4sgccO1NRYV.png?imageslim)

- 正则覆盖

  - 对最小依赖集中左部相同的函数依赖，使用合并规则进行合并 （右不单）

### 候选码求解算法

> ​    L类属性: 在F中只出现在函数依赖的左部的属性；
>
> ​    R类属性: 在F中只出现在函数依赖的右部的属性；
>
> ​    LR类属性: 分别出现在F中的函数依赖左部和右部的属性；
>
> ​    N类属性: 不在F中的函数依赖中出现的属性。
>
> - **L类属性和N类属性必包含**于任何候选码中
> - **R类属性必不包含**于任何候选码中；
> - LR类属性不能确定是否在候选码中。

对于给定的关系模式R<U, F>，其中U为属性集合，F为函数依赖集。

1. 依照函数依赖集F将R中的所有属性分为L类、R类、LR类和N类属性，令X为L、N类属性的集合，Y为LR类属性集合；
2. 若$X_F^＋=U$，则X为R的唯一候选码，结束；否则，转(3)；
3. 逐一取Y中的单一属性A，若$(XA)_F^+=U$，则XA为候选码 ，令$Y＝Y－{A}$ ，转(4)；
4. 依次取Y中的任意两个、三个……属性与XZ组成属性组，若XZ不包含已求得的候选码，求其关于F的闭包 $(XZ)_F^+$，若 $(XZ)_F^+ =U$，则XZ为候选码。直到取完Y中的所有属性为止，算法结束。

![mark](http://media.sumblog.cn/blog/20181230/1Aqe1qG0CqOL.png?imageMogr2/thumbnail/!60p)

### 模式分解的无损连接性

- 判定方法

  ![mark](http://media.sumblog.cn/blog/20181230/3NrR1QFM6SUP.png?imageMogr2/thumbnail/!60p)

  ![mark](http://media.sumblog.cn/blog/20181230/LW8NtfQ9cRli.png?imageMogr2/thumbnail/!60p)

  - 交决定差：

    分解成为两个模式，这两个模式具有无损连接性的充要条件是：
    $$
    U_1\cap U_2 \to U_1 - U_2 \in F^+
    $$
    或
    $$
    U_1\cap U_2 \to U_2 - U_1 \in F^+
    $$




### 模式分解的函数依赖性

**定义：**
$$
\mathbf { F } ^ { + } = \left( \bigcup _ { i = 1 } ^ { k } F_i \right) ^ { + }
$$

- 投影求解算法

  ![mark](http://media.sumblog.cn/blog/20181230/8RymMb1EjHKb.png?imageMogr2/thumbnail/!60p)

### 模式分解

- ![mark](http://media.sumblog.cn/blog/20181230/yAilSh8cVOXI.png?imageMogr2/thumbnail/!60p)

- ![mark](http://media.sumblog.cn/blog/20181230/eW1QRGUHjUzC.png?imageMogr2/thumbnail/!60p)





{{ self.title() }}

Author: yuxaij@gmail.com

## 叉积

可以利用二维叉积快速判断一个向量是否在 $[(a,b), (c,d)]$ 所对应的区域内。令向量 $u=(x_1,y_1), v=(x_2,y_2)$，则 
$$u \times v = x_1 y_2 - x_2 y_1$$

若 $u \times v < 0$，则说明 $v$ 在 $u$ 的左手方向，反之则是右手方向。相等时即两向量方向一致。 

## B = atan2(0, 1) 的情况

此时 $x_i = x_j$ 的情况容易处理。考虑直线的斜截式 $y=kx+b$，其他情况即求满足以下条件的点对 $i, j$：

$$x_i < x_j, ~ (y_j - y_i) / (x_j - x_i) \geq b / a$$

移项后有

$$x_i < x_j, ~ bx_i - ay_i \geq bx_j - ay_j$$ 

这是一个二维偏序，离散化后求逆序对即可。

## 旋转坐标系

当 $B \neq pi/2$ 时，顺时针旋转坐标系到 $B = \pi/2$ 即可。此时旋转角满足 $\sin(\alpha) = c/|(c,d)|, \cos(\alpha) = d/|(c,d)|$，其中 $|(c,d)|$ 表示向量 $(c,d)$ 的模长。代入各点坐标有

$$\begin{aligned}
x'_i &= x_i \cos(\alpha) - y_i \sin(\alpha) = (x_i d - y_i c) / |(c,d)| \\
y'_i &= x_i \sin(\alpha) + y_i \cos(\alpha) = (x_i c + y_i d) / |(c,d)|
\end{aligned}
$$

再代入斜截式，可以发现旋转坐标系后对一个非原点向量的角度没有影响。而判断式中的 |(c,d)| 将被消去，因此直接保留分子部分即可。

## 特殊情况 $x_i = x_j$

直接按移项后的结果处理没有影响，不过也可以按离散化的过程特殊处理。



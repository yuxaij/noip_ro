{{ self.title() }}

{{ s('description') }}

二维平面上有 $n$ 个点，其中点 $i$ 的坐标为 $(x_i, y_i)$，没有两个点的坐标相同。现在要随机选定两个点作一向量，求该向量的方向角弧度在 $[A,B] (A\leq B)$ 内的概率，保证 $A,B \in [0, pi/2]$。

随机选定两个点作向量是指，从这 $n(n-1)$ 个点对中等概率地选取一组点对做向量。注意点对 $(a,b)$ 和 $(b,a)$ 所表示的向量的方向角弧度差值为 $\pi$，方向相反。

{{ s('input format') }}
{{ self.input_file() }}

输入的第一行包含一个正整数 $n$。

接下来一行四个非负整数 $a,b,c,d$，表示方向角弧度 $A$ 所对应的向量为 $(a,b)$，方向角弧度 $B$ 所对应的向量为 $(c,d)$，保证 $a+b >0, c+d > 0$。

接下来 $n$ 行，每行两个整数 $x,y$，描述一个点。

{{ s('output format') }}
{{ self.output_file() }}

输出一行一个非负整数 $x$，表示方向角弧度在 $[A,B]$ 内的概率为 $x / n(n-1)$。

{{ s('sample') }}
{{ self.sample_text() }}

{{ s('subtasks') }}

{{ tbl('data', width = [3,2,4,2], font_size=10) }}

{{ s('hint') }}

你可以用到 $atan2(y,x)$ 来求方向角的弧度。$(1,0),(0,1),(-1,0),(0,-1)$ 这四个向量的方向角弧度分别为 $0, \pi / 2, \pm \pi, -\pi / 2$。

角度 $d$ 与弧度 $c$ 的转化为 $d = 180^{\circ} \times (c / pi)$。

你可能会用到以下公式：
$$\begin{aligned}
& \cos(\alpha+\beta) = \cos \alpha \cos \beta - \sin \alpha \sin \beta \\
& \sin(\alpha+\beta) = \sin \alpha \cos \beta + \sin \beta \cos \alpha \\
&\cos(-\alpha) = \cos(\alpha) \\
& \sin(-\alpha) = -\sin(\alpha) 
\end{aligned}
$$


{{ self.title() }}

{{ s('description') }}

有 $n$ 枚硬币排成一行，编号 $1 \sim n$。一开始，所有硬币都是正面朝下。现在每次操作将会随机挑选一个区间 $[l, r]$，并**将区间内所有正面朝下的硬币翻转为正面朝上**。重复该操作，直到所有硬币都是正面朝上为止。求期望的操作次数。

随机挑选一个区间的意思是指，在一次操作中，这 $\binom{n+1}{2}$ 个区间都有相等的概率被选中。

{{ s('input format') }}
{{ self.input_file() }}

输入的第一行包含两个正整数 $n, p$，其中 $p$ 的含义见输出格式。

{{ s('output format') }}
{{ self.output_file() }}

输出一行一个至多 300 位小数的实数，描述答案。你的答案被视为正确当且仅当与标准答案的绝对误差小于 $10^{-p}$。

{{ s('sample', 1) }}
{{ self.sample_text() }}

{{ s('subtasks') }}

{{ tbl('data', width = [3,2,2], font_size=10) }}

{{ s('hint') }}

如果你需要的话，可以考虑容斥原理：
$$ P(x_1 = 1, x_2 = 1, \dots, x_n = 1) = \sum_{y \subseteq [n]} (-1)^{|y|} P(\forall i, x_{y_i} = 0) $$

其中 $[n] = \{ 1, 2, \dots, n\}$。

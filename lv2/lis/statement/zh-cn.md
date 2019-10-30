{{ self.title() }}

{{ s('description') }}

已知序列 $a(a_1, a_2, \dots, a_m)$ 是 $1 \sim n$ 排列 $p(p_1, p_2, \dots, p_n)$ 的一个最长上升子序列，求满足条件 $p$ 的个数。 

{{ s('input format') }}
{{ self.input_file() }}

输入的第一行包含两个正整数 $n,m$。

接下来一行 $m$ 个严格递增的正整数 $a_1, a_2, \dots, a_m$，描述序列 $a$。

{{ s('output format') }}
{{ self.output_file() }}

输出一行一个整数，描述满足条件 $p$ 的个数。

{{ s('sample') }}
{{ self.sample_text() }}

{{ s('subtasks') }}

{{ tbl('data', width = [3,2,2], font_size=10) }}

{{ self.title() }}

{{ s('description') }}

考虑经典的背包问题。已知背包的大小为 $V$，有 $n$ 类物品，第 $i$ 类有 $num_i$ 个，且单个物品的体积为 $volume_i$，价值为 $value_i$。

**要求方案必须装满背包，即选出的所有物品的体积和为 $V$，保证这样的方案存在。**令 $B(b_1, b_2, \dots, b_n)$ 描述方案，其中 $b_i$ 表示方案中第 $i$ 类物品选出的个数。请求出最大化总价值的所有方案中，**字典序最小者**。

{{ s('input format') }}
{{ self.input_file() }}

输入的第一行包含两个正整数 $n, V$。

接下来 $n$ 行，每行有三个正整数 $num_i, volume_i, value_i$，描述一类物品。

{{ s('output format') }}
{{ self.output_file() }}

输出的第一行为一个非负整数，描述最大化的总价值。

接下来一行 $n$ 个非负整数，描述你的方案。其中该行的第 $i$ 个整数表示你的方案中第 $i$ 类物品选出的个数。

若你的输出中的第一行正确，则你可以获得 50\% 的分数。

{{ s('sample') }}
{{ self.sample_text() }}

{{ s('subtasks') }}

{{ tbl('data', width = [3,2,2,2,3], font_size=10) }}


{{ self.title() }}

{{ s('description') }}

给出一个大小为 $n$ 的整数序列 $a(a_1, a_2, \dots, a_n)$，序列中的元素有正有负。现在有 $q$ 个询问，每个询问给出三个参数 $s, t, k$，要求求出在区间 $[s,t]$ 中，选出恰好 $k$ 个互不相交的子区间 $[l_1, r_2]，[l_2, r_2], \dots, [l_k, r_k]$，并最大化这 $k$ 个区间的权值之和，即

$$\sum_{i=1}^{k} \sum_{j=l_i}^{r_i} a_j.$$

{{ s('input format') }}
{{ self.input_file() }}

输入的第一行包含两个正整数 $n,q$，描述序列的大小和询问的个数。

接下来一行 $n$ 个整数 $a_1, a_2, \dots, a_n$，描述序列 $a$。

接下来 $q$ 行，每行三个正整数 $s, t, k$，描述一个询问。

{{ s('output format') }}

{{ self.output_file() }}

依次对于每个询问，输出一行一个整数，描述最大化的区间权值和。若无法在对应的 $[s,t]$ 中选出 $k$ 个互不相交的子区间，则输出 `IMPOSSIBLE`。 

{{ s('sample') }}
{{ self.sample_text() }}

{{ s('subtasks') }}

{{ tbl('data', width = [4,2,2,2,2,5]) }}

{{ s('hint') }}

一般来说，你不需要考虑如何完成编号为 $20$ 的测试点。

{{ self.title() }}

{{ s('description') }}

给定一个字符串 $S[1\dots n]$ 和一个常数 $K$，请求出这个字符串有多少个前缀子字符串 $S[1 \dots p] (1 \leq p \leq n)$ 满足以下条件

$$\exists ~ string ~A,B, ~s.t., \quad S[1 \dots p] = \underbrace{\overline{ABAB \dots ABA}}_{\text{k+1个A,k个B}}$$

其中 $A,B$ 允许为空字符串。例如当 $K=3$ 时，`ssss` 和 `sss` 都是满足条件的字符串，只要分别令 A,B=`s`，而另一字符串为空即可。

{{ s('input format') }}
{{ self.input_file() }}

输入包含多组 $S,K$。每组的第一行包含两个正整数 $n, K$，第二行包含一个长度为 $n$ 的，由小写字母构成的字符串，描述 $S$。

输入以一行一个 $0$ 结束。

{{ s('output format') }}
{{ self.output_file() }}

对于每组询问，输出一行一个长度为 $n$ 的 $01$ 字符串，第 $i$ 个字符描述前缀 $S[1 \dots i]$ 是否满足条件：若为 `1` 则表示满足，为 `0` 则表示不满足。

{{ s('sample') }}
{{ self.sample_text() }}

{{ s('subtasks') }}

{{ tbl('data', width = [3,2,2,2], font_size=10) }}

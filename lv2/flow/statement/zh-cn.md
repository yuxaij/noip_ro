{{ self.title() }}

{{ s('description') }}

给出一个边带正权的流系统 $G(V,E,c,v,S,T)$，以及一个系统中的可行流，请判断该可行流是否为最大流。如果不是，求出将该可行流的流量 +1 所需要的最小代价——设当前的可行流为 F，你修改后的可行流为 F'，则修改所花费的代价为：
$$\sum_{e \in E} |F'(e) - F(e)| \times v_e $$

$F(e) \in [c(e)]$ 表示流 $F$ 在边 $e$ 上的流量，其中 $[c(e)] = \{0,1,2,\dots, c(e)\}$。将一个流的流量 $+1$ 是指将下式的值 $+1$
$$flow(F) = \sum_{(S, u) \in E} F((S, u)).$$

{{ s('input format') }}
{{ self.input_file() }}

输入包含多个流系统。对于每个流系统，输入的第一行包含两个正整数 $n, m$，描述图中点的个数 $|V|$ 和边的个数 $|E|$，点和边的编号分别为 $1\sim n$ 以及 $1 \sim m$。

输入的第二行有两个整数 $S, T$，分别描述该流系统中源和汇的编号。

接下来 $m$ 行，每行四个正整数 $a,b,c,v$，表示从 $a$ 向 $b$ 有一条容量为 $c$，权为 $v$ 的边。

接下来一行 $m$ 个非负整数，描述给出的可行流。第 $i$ 个数 $f_i$ 表示可行流在第 $i$ 条边上的流量为 $f_i$。

输入以一行两个 $0, 0$ 结束。

{{ s('output format') }}
{{ self.output_file() }}

对于每个流系统，输出一行一个数，描述答案。若该可行流为最大流，输出 `-1`。否则输出将该可行流流量 +1 的最小代价。

{{ s('sample') }}
{{ self.sample_text() }}
{{ self.title_sample_description() }}

第一个流系统的最优修改方案为：将边 $(1,2), (2,4), (3,5), (5,6)$ 的流量 $+1$，将边 $(2,4)$ 的流量 $-1$，代价为 $1+3+4+5+7=20$。

{{ s('subtasks') }}

{{ tbl('data', width = [3,2,2,2,2,2,4], font_size=10) }}

{{ s('hint') }}

可先证明对于任意整数 $f$，若存在 $flow(F) = f$，则必然存在一个 $flow(F') = \ceil{f}$，且 $\forall e \in E, ~ F'(e) \in \mathbb{N^*}$。

$\rhd$ 任何一个流 $F$ 可行的充要条件为：
$$\begin{cases}
inFlow(v) = \sum_{(u, v) \in E} F((u,v)) = \sum_{(v, u') \in E} F((v,u')) = outflow(v), &\forall v \in V, ~v \neq S, T,  \\
F(e) \in [0, c(e)], & \forall e \in E  
\end{cases} $$
